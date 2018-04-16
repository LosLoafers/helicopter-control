/* Include files */

#include "LinuxMPC_sfun.h"
#include "c1_LinuxMPC.h"
#include "c2_LinuxMPC.h"
#include "c4_LinuxMPC.h"
#include "c5_LinuxMPC.h"

/* Type Definitions */

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */
uint32_T _LinuxMPCMachineNumber_;
real_T _sfTime_;

/* Function Declarations */

/* Function Definitions */
void LinuxMPC_initializer(void)
{
}

void LinuxMPC_terminator(void)
{
}

/* SFunction Glue Code */
unsigned int sf_LinuxMPC_method_dispatcher(SimStruct *simstructPtr, unsigned int
  chartFileNumber, const char* specsCksum, int_T method, void *data)
{
  if (chartFileNumber==1) {
    c1_LinuxMPC_method_dispatcher(simstructPtr, method, data);
    return 1;
  }

  if (chartFileNumber==2) {
    c2_LinuxMPC_method_dispatcher(simstructPtr, method, data);
    return 1;
  }

  if (chartFileNumber==4) {
    c4_LinuxMPC_method_dispatcher(simstructPtr, method, data);
    return 1;
  }

  if (chartFileNumber==5) {
    c5_LinuxMPC_method_dispatcher(simstructPtr, method, data);
    return 1;
  }

  return 0;
}

unsigned int sf_LinuxMPC_process_check_sum_call( int nlhs, mxArray * plhs[], int
  nrhs, const mxArray * prhs[] )
{

#ifdef MATLAB_MEX_FILE

  char commandName[20];
  if (nrhs<1 || !mxIsChar(prhs[0]) )
    return 0;

  /* Possible call to get the checksum */
  mxGetString(prhs[0], commandName,sizeof(commandName)/sizeof(char));
  commandName[(sizeof(commandName)/sizeof(char)-1)] = '\0';
  if (strcmp(commandName,"sf_get_check_sum"))
    return 0;
  plhs[0] = mxCreateDoubleMatrix( 1,4,mxREAL);
  if (nrhs>1 && mxIsChar(prhs[1])) {
    mxGetString(prhs[1], commandName,sizeof(commandName)/sizeof(char));
    commandName[(sizeof(commandName)/sizeof(char)-1)] = '\0';
    if (!strcmp(commandName,"machine")) {
      ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(1756745947U);
      ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(3175262515U);
      ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(3640129431U);
      ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(4050157350U);
    } else if (!strcmp(commandName,"exportedFcn")) {
      ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(0U);
      ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(0U);
      ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(0U);
      ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(0U);
    } else if (!strcmp(commandName,"makefile")) {
      ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(3233190459U);
      ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(467849986U);
      ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(955474965U);
      ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(3099219602U);
    } else if (nrhs==3 && !strcmp(commandName,"chart")) {
      unsigned int chartFileNumber;
      chartFileNumber = (unsigned int)mxGetScalar(prhs[2]);
      switch (chartFileNumber) {
       case 1:
        {
          extern void sf_c1_LinuxMPC_get_check_sum(mxArray *plhs[]);
          sf_c1_LinuxMPC_get_check_sum(plhs);
          break;
        }

       case 2:
        {
          extern void sf_c2_LinuxMPC_get_check_sum(mxArray *plhs[]);
          sf_c2_LinuxMPC_get_check_sum(plhs);
          break;
        }

       case 4:
        {
          extern void sf_c4_LinuxMPC_get_check_sum(mxArray *plhs[]);
          sf_c4_LinuxMPC_get_check_sum(plhs);
          break;
        }

       case 5:
        {
          extern void sf_c5_LinuxMPC_get_check_sum(mxArray *plhs[]);
          sf_c5_LinuxMPC_get_check_sum(plhs);
          break;
        }

       default:
        ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(0.0);
        ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(0.0);
        ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(0.0);
        ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(0.0);
      }
    } else if (!strcmp(commandName,"target")) {
      ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(1764838350U);
      ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(3410240878U);
      ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(118138738U);
      ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(243351119U);
    } else {
      return 0;
    }
  } else {
    ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(3751621478U);
    ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(3452445704U);
    ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(2119792632U);
    ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(584053591U);
  }

  return 1;

#else

  return 0;

#endif

}

unsigned int sf_LinuxMPC_autoinheritance_info( int nlhs, mxArray * plhs[], int
  nrhs, const mxArray * prhs[] )
{

#ifdef MATLAB_MEX_FILE

  char commandName[32];
  char aiChksum[64];
  if (nrhs<3 || !mxIsChar(prhs[0]) )
    return 0;

  /* Possible call to get the autoinheritance_info */
  mxGetString(prhs[0], commandName,sizeof(commandName)/sizeof(char));
  commandName[(sizeof(commandName)/sizeof(char)-1)] = '\0';
  if (strcmp(commandName,"get_autoinheritance_info"))
    return 0;
  mxGetString(prhs[2], aiChksum,sizeof(aiChksum)/sizeof(char));
  aiChksum[(sizeof(aiChksum)/sizeof(char)-1)] = '\0';

  {
    unsigned int chartFileNumber;
    chartFileNumber = (unsigned int)mxGetScalar(prhs[1]);
    switch (chartFileNumber) {
     case 1:
      {
        if (strcmp(aiChksum, "hNPN2Q5ugbbbiT0Ko43kS") == 0) {
          extern mxArray *sf_c1_LinuxMPC_get_autoinheritance_info(void);
          plhs[0] = sf_c1_LinuxMPC_get_autoinheritance_info();
          break;
        }

        plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
        break;
      }

     case 2:
      {
        if (strcmp(aiChksum, "3yHfxjW4hjnhhqq6gV1XTC") == 0) {
          extern mxArray *sf_c2_LinuxMPC_get_autoinheritance_info(void);
          plhs[0] = sf_c2_LinuxMPC_get_autoinheritance_info();
          break;
        }

        plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
        break;
      }

     case 4:
      {
        if (strcmp(aiChksum, "v5wOM0Xu9imk4J4oYQSfR") == 0) {
          extern mxArray *sf_c4_LinuxMPC_get_autoinheritance_info(void);
          plhs[0] = sf_c4_LinuxMPC_get_autoinheritance_info();
          break;
        }

        plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
        break;
      }

     case 5:
      {
        if (strcmp(aiChksum, "iyq4TsZphqfYq9BGHhI2gF") == 0) {
          extern mxArray *sf_c5_LinuxMPC_get_autoinheritance_info(void);
          plhs[0] = sf_c5_LinuxMPC_get_autoinheritance_info();
          break;
        }

        plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
        break;
      }

     default:
      plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
    }
  }

  return 1;

#else

  return 0;

#endif

}

unsigned int sf_LinuxMPC_get_eml_resolved_functions_info( int nlhs, mxArray *
  plhs[], int nrhs, const mxArray * prhs[] )
{

#ifdef MATLAB_MEX_FILE

  char commandName[64];
  if (nrhs<2 || !mxIsChar(prhs[0]))
    return 0;

  /* Possible call to get the get_eml_resolved_functions_info */
  mxGetString(prhs[0], commandName,sizeof(commandName)/sizeof(char));
  commandName[(sizeof(commandName)/sizeof(char)-1)] = '\0';
  if (strcmp(commandName,"get_eml_resolved_functions_info"))
    return 0;

  {
    unsigned int chartFileNumber;
    chartFileNumber = (unsigned int)mxGetScalar(prhs[1]);
    switch (chartFileNumber) {
     case 1:
      {
        extern const mxArray *sf_c1_LinuxMPC_get_eml_resolved_functions_info
          (void);
        mxArray *persistentMxArray = (mxArray *)
          sf_c1_LinuxMPC_get_eml_resolved_functions_info();
        plhs[0] = mxDuplicateArray(persistentMxArray);
        mxDestroyArray(persistentMxArray);
        break;
      }

     case 2:
      {
        extern const mxArray *sf_c2_LinuxMPC_get_eml_resolved_functions_info
          (void);
        mxArray *persistentMxArray = (mxArray *)
          sf_c2_LinuxMPC_get_eml_resolved_functions_info();
        plhs[0] = mxDuplicateArray(persistentMxArray);
        mxDestroyArray(persistentMxArray);
        break;
      }

     case 4:
      {
        extern const mxArray *sf_c4_LinuxMPC_get_eml_resolved_functions_info
          (void);
        mxArray *persistentMxArray = (mxArray *)
          sf_c4_LinuxMPC_get_eml_resolved_functions_info();
        plhs[0] = mxDuplicateArray(persistentMxArray);
        mxDestroyArray(persistentMxArray);
        break;
      }

     case 5:
      {
        extern const mxArray *sf_c5_LinuxMPC_get_eml_resolved_functions_info
          (void);
        mxArray *persistentMxArray = (mxArray *)
          sf_c5_LinuxMPC_get_eml_resolved_functions_info();
        plhs[0] = mxDuplicateArray(persistentMxArray);
        mxDestroyArray(persistentMxArray);
        break;
      }

     default:
      plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
    }
  }

  return 1;

#else

  return 0;

#endif

}

void LinuxMPC_debug_initialize(void)
{
  _LinuxMPCMachineNumber_ = sf_debug_initialize_machine("LinuxMPC","sfun",0,4,0,
    0,0);
  sf_debug_set_machine_event_thresholds(_LinuxMPCMachineNumber_,0,0);
  sf_debug_set_machine_data_thresholds(_LinuxMPCMachineNumber_,0);
}

void LinuxMPC_register_exported_symbols(SimStruct* S)
{
}

static mxArray* sRtwOptimizationInfoStruct= NULL;
mxArray* load_LinuxMPC_optimization_info(void)
{
  if (sRtwOptimizationInfoStruct==NULL) {
    sRtwOptimizationInfoStruct = sf_load_rtw_optimization_info("LinuxMPC",
      "LinuxMPC");
    mexMakeArrayPersistent(sRtwOptimizationInfoStruct);
  }

  return(sRtwOptimizationInfoStruct);
}

void unload_LinuxMPC_optimization_info(void)
{
  if (sRtwOptimizationInfoStruct!=NULL) {
    mxDestroyArray(sRtwOptimizationInfoStruct);
    sRtwOptimizationInfoStruct = NULL;
  }
}
