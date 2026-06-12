#include "main.h"
#include "ctr.h"

///////////////
// Variables //
///////////////
// Control State
int ctrMode;
//String ctrStateString;

int ctrInsState;
int crtResState;
int crtAguaState;

// Control vars
int   ctrInTermostato;
int   ctrInQuemador;
int   ctrOutAgua;
int   ctrOutQuemador;
int   ctrContQuemador;

int   ctrOutAchique;

float ctrTempResPrim;
float ctrTempResInye;
float ctrTempAgua;

void _ctrInsUdpate(void)
{
  ctrInTermostato = InDig[TERMOSTATO_IN];
  ctrInQuemador   = InDig[QUEMADOR_IN];

  ctrTempResPrim  = mbfTemp[TEMP_RES_PRIM];
  ctrTempResInye  = mbfTemp[TEMP_RES_INYE];
  ctrTempAgua     = mbfTemp[TEMP_AGUA];

  // TODO guardar en Cfg
  ctrContQuemador = 0;
}

void _ctrOutsUpdate()
{
  OutDig[AGUA_OUT]     = ctrOutAgua;
  OutDig[ACHIQUE_OUT]  = ctrOutAchique;
  OutDig[QUEMADOR_OUT] = ctrOutQuemador;
}

void _ctrInsLoop()
{
  switch (ctrInsState)
  {
    case CTR_THERMO_OFF:
      if (ctrInTermostato == IN_ON)
      {
        crtResState = CTR_RES_START;
        ctrInsState = CTR_THERMO_ON;
      }
      break;

    case CTR_THERMO_ON:
      if (ctrInTermostato == IN_OFF)
      {
        crtResState = CTR_RES_STOP;
        ctrInsState = CTR_THERMO_OFF;
      }
      break;
  }
}

void _ctrResLoop()
{
  switch (crtResState)
  {
    case CTR_RES_STANDBY:
      TriacCtr[RES_PRIN_TRC]  = TRIAC_OFF;
      TriacCtr[TEMP_RES_INYE] = TRIAC_OFF;

      break;

    case CTR_RES_START:
      if (ctrTempResPrim < (float)cfgResPrimInyeTemp)
      {
        TriacCtr[RES_PRIN_TRC] = TRIAC_ON;
        TriacCtr[TEMP_RES_INYE] = TRIAC_OFF;
      }
      else
      {
        TriacCtr[RES_PRIN_TRC] = TRIAC_ON;
        //TriacCtr[TEMP_RES_INYE] = TRIAC_ON;
        crtResState = CTR_RES_STATE2;
      }
      break;

    case CTR_RES_STATE2:
      // Control Resistencia principal
      if (ctrTempResPrim > (float)(cfgResPrimInyeTemp - cfgResPrimHystTemp) &&
          ctrTempResPrim < (float)(cfgResPrimConsTemp))
        // Mantenemos la resistencia principal hasta su consigna
        TriacCtr[RES_PRIN_TRC] = TRIAC_ON;
      else if (ctrTempResPrim <= (float)(cfgResPrimInyeTemp - cfgResPrimHystTemp))
      {
        // La resistencia principal ha bajado
        // TODO: Alarma!!!
      }
      else if (ctrTempResPrim >= (float)cfgResPrimConsTemp)
      {
        // Hemos llegado a la consigna
        TriacCtr[RES_PRIN_TRC] = TRIAC_OFF;
        // TODO
        crtResState = CTR_RES_STATE3;

        // Arrancamos la bomba y quemador
        crtAguaState = CTR_AGUA_START;
      }

      // Control Resistencia inyector
      // TODO
      break;

    case CTR_RES_STATE3:
      
      if (ctrTempResPrim > (float)(cfgResPrimConsTemp - cfgResPrimHystTemp))
        // Mantengo apagado
        TriacCtr[RES_PRIN_TRC] = TRIAC_OFF;
      else
      {
        // Reniciamos ciclo
        TriacCtr[RES_PRIN_TRC] = TRIAC_ON;
        crtResState = CTR_RES_STATE2;
      }
      break;

    case CTR_RES_STOP:
      // TODO Stop
      crtAguaState = CTR_AGUA_STOP;
      crtResState = CTR_RES_STANDBY;
      break;
  }
}

void _ctrAguaLoop()
{
  switch (crtAguaState)
  {
    case CTR_AGUA_STANDBY:
      ctrOutAgua     = OUT_OFF;
      ctrOutQuemador = OUT_OFF;
      break;

    case CTR_AGUA_START:
      ctrOutAgua     = OUT_ON;
      ctrOutQuemador = OUT_ON;
      ctrOutQuemador++;
      crtAguaState = CTR_AGUA_STATE2;
      break;

    case CTR_AGUA_STATE2:
      ctrOutAgua     = OUT_ON;
      ctrOutQuemador = OUT_ON;

      // TODO
      // Confimación del quemador!!!

      if (ctrTempAgua > (float)cfgAguaConsTemp)
        crtAguaState = CTR_AGUA_STATE3;

      break;

    case CTR_AGUA_STATE3:
      ctrOutAgua     = OUT_ON;
      ctrOutQuemador = OUT_OFF;

      if (ctrTempAgua <= (float)(cfgAguaConsTemp - cfgAguaHystTemp))
        crtAguaState = CTR_AGUA_STATE2;

      break;

    case CTR_AGUA_STOP:
      // TODO Stop
      crtAguaState = CTR_AGUA_STANDBY;
      break;
  }
}

////////////////
// Ctr set up //
////////////////
void _CtrSetup(void)
{
  ctrMode = MODE_AUTO;

  ctrInsState  = CTR_THERMO_OFF;
  crtResState  = CTR_RES_STANDBY;
  crtAguaState = CTR_AGUA_STANDBY;
}

///////////////////////
// Ctr state machine //
///////////////////////
void _CtrLoop(void)
{
  _ctrInsUdpate();

  _ctrInsLoop();
  _ctrResLoop();
  _ctrAguaLoop();

  _ctrOutsUpdate();

  /*
  #if (_USE_ALARM_ == 1)
  // TODO
  if (alarm[AL_ERROR0] == 1)
  {
    // Incremenetar timer
  }
  else
  {
    //Resetear timer
  }
  #endif
  */
}
