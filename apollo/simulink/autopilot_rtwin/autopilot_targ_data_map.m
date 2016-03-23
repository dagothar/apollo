  function targMap = targDataMap(),

  ;%***********************
  ;% Create Parameter Map *
  ;%***********************
      
    nTotData      = 0; %add to this count as we go
    nTotSects     = 2;
    sectIdxOffset = 0;
    
    ;%
    ;% Define dummy sections & preallocate arrays
    ;%
    dumSection.nData = -1;  
    dumSection.data  = [];
    
    dumData.logicalSrcIdx = -1;
    dumData.dtTransOffset = -1;
    
    ;%
    ;% Init/prealloc paramMap
    ;%
    paramMap.nSections           = nTotSects;
    paramMap.sectIdxOffset       = sectIdxOffset;
      paramMap.sections(nTotSects) = dumSection; %prealloc
    paramMap.nTotData            = -1;
    
    ;%
    ;% Auto data (autopilot_P)
    ;%
      section.nData     = 28;
      section.data(28)  = dumData; %prealloc
      
	  ;% autopilot_P.DerivativeGain_Gain
	  section.data(1).logicalSrcIdx = 2;
	  section.data(1).dtTransOffset = 0;
	
	  ;% autopilot_P.Filter_IC
	  section.data(2).logicalSrcIdx = 3;
	  section.data(2).dtTransOffset = 1;
	
	  ;% autopilot_P.FilterCoefficient_Gain
	  section.data(3).logicalSrcIdx = 4;
	  section.data(3).dtTransOffset = 2;
	
	  ;% autopilot_P.IntegralGain_Gain
	  section.data(4).logicalSrcIdx = 5;
	  section.data(4).dtTransOffset = 3;
	
	  ;% autopilot_P.Integrator_IC
	  section.data(5).logicalSrcIdx = 6;
	  section.data(5).dtTransOffset = 4;
	
	  ;% autopilot_P.ProportionalGain_Gain
	  section.data(6).logicalSrcIdx = 7;
	  section.data(6).dtTransOffset = 5;
	
	  ;% autopilot_P.Switch_Threshold
	  section.data(7).logicalSrcIdx = 8;
	  section.data(7).dtTransOffset = 6;
	
	  ;% autopilot_P.DerivativeGain_Gain_m
	  section.data(8).logicalSrcIdx = 9;
	  section.data(8).dtTransOffset = 7;
	
	  ;% autopilot_P.Filter_IC_f
	  section.data(9).logicalSrcIdx = 10;
	  section.data(9).dtTransOffset = 8;
	
	  ;% autopilot_P.FilterCoefficient_Gain_h
	  section.data(10).logicalSrcIdx = 11;
	  section.data(10).dtTransOffset = 9;
	
	  ;% autopilot_P.IntegralGain_Gain_m
	  section.data(11).logicalSrcIdx = 12;
	  section.data(11).dtTransOffset = 10;
	
	  ;% autopilot_P.Integrator_IC_m
	  section.data(12).logicalSrcIdx = 13;
	  section.data(12).dtTransOffset = 11;
	
	  ;% autopilot_P.ProportionalGain_Gain_h
	  section.data(13).logicalSrcIdx = 14;
	  section.data(13).dtTransOffset = 12;
	
	  ;% autopilot_P.Switch_Threshold_a
	  section.data(14).logicalSrcIdx = 15;
	  section.data(14).dtTransOffset = 13;
	
	  ;% autopilot_P.DerivativeGain_Gain_j
	  section.data(15).logicalSrcIdx = 16;
	  section.data(15).dtTransOffset = 14;
	
	  ;% autopilot_P.Filter_IC_a
	  section.data(16).logicalSrcIdx = 17;
	  section.data(16).dtTransOffset = 15;
	
	  ;% autopilot_P.FilterCoefficient_Gain_o
	  section.data(17).logicalSrcIdx = 18;
	  section.data(17).dtTransOffset = 16;
	
	  ;% autopilot_P.IntegralGain_Gain_i
	  section.data(18).logicalSrcIdx = 19;
	  section.data(18).dtTransOffset = 17;
	
	  ;% autopilot_P.Integrator_IC_n
	  section.data(19).logicalSrcIdx = 20;
	  section.data(19).dtTransOffset = 18;
	
	  ;% autopilot_P.ProportionalGain_Gain_a
	  section.data(20).logicalSrcIdx = 21;
	  section.data(20).dtTransOffset = 19;
	
	  ;% autopilot_P.Switch_Threshold_e
	  section.data(21).logicalSrcIdx = 22;
	  section.data(21).dtTransOffset = 20;
	
	  ;% autopilot_P.DerivativeGain_Gain_k
	  section.data(22).logicalSrcIdx = 23;
	  section.data(22).dtTransOffset = 21;
	
	  ;% autopilot_P.Filter_IC_d
	  section.data(23).logicalSrcIdx = 24;
	  section.data(23).dtTransOffset = 22;
	
	  ;% autopilot_P.FilterCoefficient_Gain_b
	  section.data(24).logicalSrcIdx = 25;
	  section.data(24).dtTransOffset = 23;
	
	  ;% autopilot_P.IntegralGain_Gain_k
	  section.data(25).logicalSrcIdx = 26;
	  section.data(25).dtTransOffset = 24;
	
	  ;% autopilot_P.Integrator_IC_l
	  section.data(26).logicalSrcIdx = 27;
	  section.data(26).dtTransOffset = 25;
	
	  ;% autopilot_P.ProportionalGain_Gain_e
	  section.data(27).logicalSrcIdx = 28;
	  section.data(27).dtTransOffset = 26;
	
	  ;% autopilot_P.Switch_Threshold_b
	  section.data(28).logicalSrcIdx = 29;
	  section.data(28).dtTransOffset = 27;
	
      nTotData = nTotData + section.nData;
      paramMap.sections(1) = section;
      clear section
      
      section.nData     = 6;
      section.data(6)  = dumData; %prealloc
      
	  ;% autopilot_P.PacketInput_PacketID
	  section.data(1).logicalSrcIdx = 30;
	  section.data(1).dtTransOffset = 0;
	
	  ;% autopilot_P.PacketOutput_PacketID
	  section.data(2).logicalSrcIdx = 31;
	  section.data(2).dtTransOffset = 1;
	
	  ;% autopilot_P.BitwiseOperator_BitMask
	  section.data(3).logicalSrcIdx = 32;
	  section.data(3).dtTransOffset = 2;
	
	  ;% autopilot_P.BitwiseOperator_BitMask_f
	  section.data(4).logicalSrcIdx = 33;
	  section.data(4).dtTransOffset = 3;
	
	  ;% autopilot_P.BitwiseOperator_BitMask_k
	  section.data(5).logicalSrcIdx = 34;
	  section.data(5).dtTransOffset = 4;
	
	  ;% autopilot_P.BitwiseOperator_BitMask_a
	  section.data(6).logicalSrcIdx = 35;
	  section.data(6).dtTransOffset = 5;
	
      nTotData = nTotData + section.nData;
      paramMap.sections(2) = section;
      clear section
      
    
      ;%
      ;% Non-auto Data (parameter)
      ;%
    

    ;%
    ;% Add final counts to struct.
    ;%
    paramMap.nTotData = nTotData;
    


  ;%**************************
  ;% Create Block Output Map *
  ;%**************************
      
    nTotData      = 0; %add to this count as we go
    nTotSects     = 3;
    sectIdxOffset = 0;
    
    ;%
    ;% Define dummy sections & preallocate arrays
    ;%
    dumSection.nData = -1;  
    dumSection.data  = [];
    
    dumData.logicalSrcIdx = -1;
    dumData.dtTransOffset = -1;
    
    ;%
    ;% Init/prealloc sigMap
    ;%
    sigMap.nSections           = nTotSects;
    sigMap.sectIdxOffset       = sectIdxOffset;
      sigMap.sections(nTotSects) = dumSection; %prealloc
    sigMap.nTotData            = -1;
    
    ;%
    ;% Auto data (autopilot_B)
    ;%
      section.nData     = 33;
      section.data(33)  = dumData; %prealloc
      
	  ;% autopilot_B.PacketInput_o3
	  section.data(1).logicalSrcIdx = 0;
	  section.data(1).dtTransOffset = 0;
	
	  ;% autopilot_B.PacketInput_o4
	  section.data(2).logicalSrcIdx = 1;
	  section.data(2).dtTransOffset = 2;
	
	  ;% autopilot_B.PacketInput_o5
	  section.data(3).logicalSrcIdx = 2;
	  section.data(3).dtTransOffset = 9;
	
	  ;% autopilot_B.PacketInput_o6
	  section.data(4).logicalSrcIdx = 3;
	  section.data(4).dtTransOffset = 15;
	
	  ;% autopilot_B.RateTransition3
	  section.data(5).logicalSrcIdx = 4;
	  section.data(5).dtTransOffset = 23;
	
	  ;% autopilot_B.RateTransition4
	  section.data(6).logicalSrcIdx = 5;
	  section.data(6).dtTransOffset = 25;
	
	  ;% autopilot_B.RateTransition5
	  section.data(7).logicalSrcIdx = 6;
	  section.data(7).dtTransOffset = 32;
	
	  ;% autopilot_B.RateTransition6
	  section.data(8).logicalSrcIdx = 7;
	  section.data(8).dtTransOffset = 38;
	
	  ;% autopilot_B.DataTypeConversion
	  section.data(9).logicalSrcIdx = 8;
	  section.data(9).dtTransOffset = 46;
	
	  ;% autopilot_B.DerivativeGain
	  section.data(10).logicalSrcIdx = 9;
	  section.data(10).dtTransOffset = 47;
	
	  ;% autopilot_B.FilterCoefficient
	  section.data(11).logicalSrcIdx = 10;
	  section.data(11).dtTransOffset = 48;
	
	  ;% autopilot_B.IntegralGain
	  section.data(12).logicalSrcIdx = 11;
	  section.data(12).dtTransOffset = 49;
	
	  ;% autopilot_B.ProportionalGain
	  section.data(13).logicalSrcIdx = 12;
	  section.data(13).dtTransOffset = 50;
	
	  ;% autopilot_B.Switch
	  section.data(14).logicalSrcIdx = 13;
	  section.data(14).dtTransOffset = 51;
	
	  ;% autopilot_B.DataTypeConversion_o
	  section.data(15).logicalSrcIdx = 14;
	  section.data(15).dtTransOffset = 52;
	
	  ;% autopilot_B.DerivativeGain_e
	  section.data(16).logicalSrcIdx = 15;
	  section.data(16).dtTransOffset = 53;
	
	  ;% autopilot_B.FilterCoefficient_f
	  section.data(17).logicalSrcIdx = 16;
	  section.data(17).dtTransOffset = 54;
	
	  ;% autopilot_B.IntegralGain_k
	  section.data(18).logicalSrcIdx = 17;
	  section.data(18).dtTransOffset = 55;
	
	  ;% autopilot_B.ProportionalGain_i
	  section.data(19).logicalSrcIdx = 18;
	  section.data(19).dtTransOffset = 56;
	
	  ;% autopilot_B.Switch_l
	  section.data(20).logicalSrcIdx = 19;
	  section.data(20).dtTransOffset = 57;
	
	  ;% autopilot_B.Sum
	  section.data(21).logicalSrcIdx = 20;
	  section.data(21).dtTransOffset = 58;
	
	  ;% autopilot_B.DataTypeConversion_c
	  section.data(22).logicalSrcIdx = 21;
	  section.data(22).dtTransOffset = 59;
	
	  ;% autopilot_B.DerivativeGain_i
	  section.data(23).logicalSrcIdx = 22;
	  section.data(23).dtTransOffset = 60;
	
	  ;% autopilot_B.FilterCoefficient_c
	  section.data(24).logicalSrcIdx = 23;
	  section.data(24).dtTransOffset = 61;
	
	  ;% autopilot_B.IntegralGain_a
	  section.data(25).logicalSrcIdx = 24;
	  section.data(25).dtTransOffset = 62;
	
	  ;% autopilot_B.ProportionalGain_o
	  section.data(26).logicalSrcIdx = 25;
	  section.data(26).dtTransOffset = 63;
	
	  ;% autopilot_B.Switch_i
	  section.data(27).logicalSrcIdx = 26;
	  section.data(27).dtTransOffset = 64;
	
	  ;% autopilot_B.DataTypeConversion_l
	  section.data(28).logicalSrcIdx = 27;
	  section.data(28).dtTransOffset = 65;
	
	  ;% autopilot_B.DerivativeGain_ei
	  section.data(29).logicalSrcIdx = 28;
	  section.data(29).dtTransOffset = 66;
	
	  ;% autopilot_B.FilterCoefficient_e
	  section.data(30).logicalSrcIdx = 29;
	  section.data(30).dtTransOffset = 67;
	
	  ;% autopilot_B.IntegralGain_m
	  section.data(31).logicalSrcIdx = 30;
	  section.data(31).dtTransOffset = 68;
	
	  ;% autopilot_B.ProportionalGain_l
	  section.data(32).logicalSrcIdx = 31;
	  section.data(32).dtTransOffset = 69;
	
	  ;% autopilot_B.Switch_e
	  section.data(33).logicalSrcIdx = 32;
	  section.data(33).dtTransOffset = 70;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(1) = section;
      clear section
      
      section.nData     = 3;
      section.data(3)  = dumData; %prealloc
      
	  ;% autopilot_B.PacketInput_o1
	  section.data(1).logicalSrcIdx = 33;
	  section.data(1).dtTransOffset = 0;
	
	  ;% autopilot_B.PacketInput_o2
	  section.data(2).logicalSrcIdx = 34;
	  section.data(2).dtTransOffset = 1;
	
	  ;% autopilot_B.RateTransition2
	  section.data(3).logicalSrcIdx = 35;
	  section.data(3).dtTransOffset = 2;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(2) = section;
      clear section
      
      section.nData     = 4;
      section.data(4)  = dumData; %prealloc
      
	  ;% autopilot_B.LogicalOperator
	  section.data(1).logicalSrcIdx = 36;
	  section.data(1).dtTransOffset = 0;
	
	  ;% autopilot_B.LogicalOperator_n
	  section.data(2).logicalSrcIdx = 37;
	  section.data(2).dtTransOffset = 1;
	
	  ;% autopilot_B.LogicalOperator_i
	  section.data(3).logicalSrcIdx = 38;
	  section.data(3).dtTransOffset = 2;
	
	  ;% autopilot_B.LogicalOperator_d
	  section.data(4).logicalSrcIdx = 39;
	  section.data(4).dtTransOffset = 3;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(3) = section;
      clear section
      
    
      ;%
      ;% Non-auto Data (signal)
      ;%
    

    ;%
    ;% Add final counts to struct.
    ;%
    sigMap.nTotData = nTotData;
    


  ;%*******************
  ;% Create DWork Map *
  ;%*******************
      
    nTotData      = 0; %add to this count as we go
    nTotSects     = 1;
    sectIdxOffset = 3;
    
    ;%
    ;% Define dummy sections & preallocate arrays
    ;%
    dumSection.nData = -1;  
    dumSection.data  = [];
    
    dumData.logicalSrcIdx = -1;
    dumData.dtTransOffset = -1;
    
    ;%
    ;% Init/prealloc dworkMap
    ;%
    dworkMap.nSections           = nTotSects;
    dworkMap.sectIdxOffset       = sectIdxOffset;
      dworkMap.sections(nTotSects) = dumSection; %prealloc
    dworkMap.nTotData            = -1;
    
    ;%
    ;% Auto data (autopilot_DWork)
    ;%
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% autopilot_DWork.Scope_PWORK.LoggedData
	  section.data(1).logicalSrcIdx = 0;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(1) = section;
      clear section
      
    
      ;%
      ;% Non-auto Data (dwork)
      ;%
    

    ;%
    ;% Add final counts to struct.
    ;%
    dworkMap.nTotData = nTotData;
    


  ;%
  ;% Add individual maps to base struct.
  ;%

  targMap.paramMap  = paramMap;    
  targMap.signalMap = sigMap;
  targMap.dworkMap  = dworkMap;
  
  ;%
  ;% Add checksums to base struct.
  ;%


  targMap.checksum0 = 3104530854;
  targMap.checksum1 = 3537910531;
  targMap.checksum2 = 3301480833;
  targMap.checksum3 = 2426685723;

