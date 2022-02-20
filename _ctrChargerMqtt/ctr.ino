
////////////////
// Ctr set up //
////////////////
void _CtrSetup(void)
{
  ControlState = STATE_CHARGE_BATTA;
  ControlTick = millis();
}

///////////////////////
// Ctr state machine //
///////////////////////
void _CtrLoop(void)
{
  // Control de Generador
  switch (ControlState)
  {
    case STATE_CHARGE_BATTA:
      OutBattA = OUT_ON;
      OutBattB = OUT_OFF;
      OutBattC = OUT_OFF;
      
      // Salto por tiempo
      if (millis() - ControlTick >= (cfgBattAmins*_SCALE_15M_))
      {
        ControlTick = millis();
        ControlState = STATE_CHARGE_BATTAB;      
      }
      // Salto por tensión
      if (VbattIn > (float)cfgBattAvolts/10)
      {
        ControlTick = millis();
        ControlState = STATE_CHARGE_BATTAB;       
      }
      break;

    case STATE_CHARGE_BATTAB:
      OutBattA = OUT_ON;
      OutBattB = OUT_ON;
      OutBattC = OUT_OFF;
      if (millis() - ControlTick >= cfgBattTsecs*1000)
      {
        ControlTick = millis();
        ControlState = STATE_CHARGE_BATTB;      
      }
      break;

    case STATE_CHARGE_BATTB:
      OutBattA = OUT_OFF;
      OutBattB = OUT_ON;
      OutBattC = OUT_OFF;
      
      // Salto por tiempo
      if (millis() - ControlTick >= (cfgBattBmins*_SCALE_15M_))
      {
        ControlTick = millis();
        ControlState = STATE_CHARGE_BATTBC;     
      }
      // Salto por tensión
      if (VbattIn > (float)cfgBattBvolts/10)
      {
        ControlTick = millis();
        ControlState = STATE_CHARGE_BATTBC;
      }
      break;

    case STATE_CHARGE_BATTBC:
      OutBattA = OUT_OFF;
      OutBattB = OUT_ON;
      OutBattC = OUT_ON;
      if (millis() - ControlTick >= cfgBattTsecs*1000)
      {
        ControlTick = millis();
        ControlState = STATE_CHARGE_BATTC;
      }
      break;

    case STATE_CHARGE_BATTC:
      OutBattA = OUT_OFF;
      OutBattB = OUT_OFF;
      OutBattC = OUT_ON;

      // Salto por tiempo
      if (millis() - ControlTick >= (cfgBattCmins*_SCALE_15M_))
      {
        ControlTick = millis();
        ControlState = STATE_CHARGE_BATTCA;   
      }
      // Salto por tensión
      if (VbattIn > (float)cfgBattCvolts/10)
      {
        ControlTick = millis();
        ControlState = STATE_CHARGE_BATTCA;
      }
      break;

    case STATE_CHARGE_BATTCA:
      OutBattA = OUT_ON;
      OutBattB = OUT_OFF;
      OutBattC = OUT_ON;
      if (millis() - ControlTick >= cfgBattTsecs*1000)
      {
        ControlTick = millis();
        ControlState = STATE_CHARGE_BATTA;
      }
      break;
      
  }
}
