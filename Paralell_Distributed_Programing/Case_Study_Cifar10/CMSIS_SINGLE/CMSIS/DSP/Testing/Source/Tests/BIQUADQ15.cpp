#include "BIQUADQ15.h"
#include <stdio.h>
#include "Error.h"


/*

Accuracy issues on biquad df1 q15
It will have to be reworked

*/
#define SNR_THRESHOLD 30

#define ABS_ERROR_Q15 ((q15_t)500)

#if defined(ARM_MATH_MVEF) && !defined(ARM_MATH_AUTOVECTORIZE)
static __ALIGNED(8) q15_t coeffArray[32];
#endif 

    void BIQUADQ15::test_biquad_cascade_df1()
    {


        q15_t *statep = state.ptr();
        const q15_t *coefsp = coefs.ptr();
        
        const q15_t *inputp = inputs.ptr();
        q15_t *outp = output.ptr();

        int blockSize;

        

        /*

        Python script is generating different tests with
        different blockSize and numTaps.

        We loop on those configs.

        */
        
           blockSize = inputs.nbSamples() >> 1;

           /*

           The filter is initialized with the coefs, blockSize and numTaps.

           */

           arm_biquad_cascade_df1_init_q15(&this->S,3,coefsp,statep,2);


           /*
           
           Python script is filtering a 2*blockSize number of samples.
           We do the same filtering in two pass to check (indirectly that
           the state management of the fir is working.)

           */

           arm_biquad_cascade_df1_q15(&this->S,inputp,outp,blockSize);
           outp += blockSize;
           
           inputp += blockSize;
           arm_biquad_cascade_df1_q15(&this->S,inputp,outp,blockSize);
           outp += blockSize;




           ASSERT_EMPTY_TAIL(output);

           ASSERT_SNR(output,ref,(q15_t)SNR_THRESHOLD);

           ASSERT_NEAR_EQ(output,ref,ABS_ERROR_Q15);
  

    } 

 
    void BIQUADQ15::setUp(Testing::testID_t id,std::vector<Testing::param_t>& params,Client::PatternMgr *mgr)
    {
      

       
       switch(id)
       {
        case BIQUADQ15::TEST_BIQUAD_CASCADE_DF1_1:
        break;

       }
      

       inputs.reload(BIQUADQ15::BIQUADINPUTS_Q15_ID,mgr);
       coefs.reload(BIQUADQ15::BIQUADCOEFS_Q15_ID,mgr);
       ref.reload(BIQUADQ15::BIQUADREFS_Q15_ID,mgr);

       output.create(ref.nbSamples(),BIQUADQ15::OUT_Q15_ID,mgr);
       /* max 4 * nbTaps as generated by Python script */
       /* Same OUTID is reused. So linked to same output file. If it is dumped
       it may overwrite the output
       */
       state.create(32,BIQUADQ15::OUT_Q15_ID,mgr);
    }

    void BIQUADQ15::tearDown(Testing::testID_t id,Client::PatternMgr *mgr)
    {
        output.dump(mgr);
    }
