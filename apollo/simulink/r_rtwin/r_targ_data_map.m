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
    ;% Auto data (r_P)
    ;%
      section.nData     = 28;
      section.data(28)  = dumData; %prealloc
      
	  ;% r_P.DerivativeGain_Gain
	  section.data(1).logicalSrcIdx = 2;
	  section.data(1).dtTransOffset = 0;
	
	  ;% r_P.Filter_IC
	  section.data(2).logicalSrcIdx = 3;
	  section.data(2).dtTransOffset = 1;
	
	  ;% r_P.FilterCoefficient_Gain
	  section.data(3).logicalSrcIdx = 4;
	  section.data(3).dtTransOffset = 2;
	
	  ;% r_P.IntegralGain_Gain
	  section.data(4).logicalSrcIdx = 5;
	  section.data(4).dtTransOffset = 3;
	
	  ;% r_P.Integrator_IC
	  section.data(5).logicalSrcIdx = 6;
	  section.data(5).dtTransOffset = 4;
	
	  ;% r_P.ProportionalGain_Gain
	  section.data(6).logicalSrcIdx = 7;
	  section.data(6).dtTransOffset = 5;
	
	  ;% r_P.Switch_Threshold
	  section.data(7).logicalSrcIdx = 8;
	  section.data(7).dtTransOffset = 6;
	
	  ;% r_P.DerivativeGain_Gain_i
	  section.data(8).logicalSrcIdx = 9;
	  section.data(8).dtTransOffset = 7;
	
	  ;% r_P.Filter_IC_k
	  section.data(9).logicalSrcIdx = 10;
	  section.data(9).dtTransOffset = 8;
	
	  ;% r_P.FilterCoefficient_Gain_c
	  section.data(10).logicalSrcIdx = 11;
	  section.data(10).dtTransOffset = 9;
	
	  ;% r_P.IntegralGain_Gain_e
	  section.data(11).logicalSrcIdx = 12;
	  section.data(11).dtTransOffset = 10;
	
	  ;% r_P.Integrator_IC_d
	  section.data(12).logicalSrcIdx = 13;
	  section.data(12).dtTransOffset = 11;
	
	  ;% r_P.ProportionalGain_Gain_e
	  section.data(13).logicalSrcIdx = 14;
	  section.data(13).dtTransOffset = 12;
	
	  ;% r_P.Switch_Threshold_n
	  section.data(14).logicalSrcIdx = 15;
	  section.data(14).dtTransOffset = 13;
	
	  ;% r_P.DerivativeGain_Gain_j
	  section.data(15).logicalSrcIdx = 16;
	  section.data(15).dtTransOffset = 14;
	
	  ;% r_P.Filter_IC_a
	  section.data(16).logicalSrcIdx = 17;
	  section.data(16).dtTransOffset = 15;
	
	  ;% r_P.FilterCoefficient_Gain_j
	  section.data(17).logicalSrcIdx = 18;
	  section.data(17).dtTransOffset = 16;
	
	  ;% r_P.IntegralGain_Gain_c
	  section.data(18).logicalSrcIdx = 19;
	  section.data(18).dtTransOffset = 17;
	
	  ;% r_P.Integrator_IC_h
	  section.data(19).logicalSrcIdx = 20;
	  section.data(19).dtTransOffset = 18;
	
	  ;% r_P.ProportionalGain_Gain_f
	  section.data(20).logicalSrcIdx = 21;
	  section.data(20).dtTransOffset = 19;
	
	  ;% r_P.Switch_Threshold_i
	  section.data(21).logicalSrcIdx = 22;
	  section.data(21).dtTransOffset = 20;
	
	  ;% r_P.DerivativeGain_Gain_o
	  section.data(22).logicalSrcIdx = 23;
	  section.data(22).dtTransOffset = 21;
	
	  ;% r_P.Filter_IC_j
	  section.data(23).logicalSrcIdx = 24;
	  section.data(23).dtTransOffset = 22;
	
	  ;% r_P.FilterCoefficient_Gain_e
	  section.data(24).logicalSrcIdx = 25;
	  section.data(24).dtTransOffset = 23;
	
	  ;% r_P.IntegralGain_Gain_d
	  section.data(25).logicalSrcIdx = 26;
	  section.data(25).dtTransOffset = 24;
	
	  ;% r_P.Integrator_IC_m
	  section.data(26).logicalSrcIdx = 27;
	  section.data(26).dtTransOffset = 25;
	
	  ;% r_P.ProportionalGain_Gain_h
	  section.data(27).logicalSrcIdx = 28;
	  section.data(27).dtTransOffset = 26;
	
	  ;% r_P.Switch_Threshold_e
	  section.data(28).logicalSrcIdx = 29;
	  section.data(28).dtTransOffset = 27;
	
      nTotData = nTotData + section.nData;
      paramMap.sections(1) = section;
      clear section
      
      section.nData     = 6;
      section.data(6)  = dumData; %prealloc
      
	  ;% r_P.PacketInput_PacketID
	  section.data(1).logicalSrcIdx = 30;
	  section.data(1).dtTransOffset = 0;
	
	  ;% r_P.PacketOutput_PacketID
	  section.data(2).logicalSrcIdx = 31;
	  section.data(2).dtTransOffset = 1;
	
	  ;% r_P.BitwiseOperator_BitMask
	  section.data(3).logicalSrcIdx = 32;
	  section.data(3).dtTransOffset = 2;
	
	  ;% r_P.BitwiseOperator_BitMask_m
	  section.data(4).logicalSrcIdx = 33;
	  section.data(4).dtTransOffset = 3;
	
	  ;% r_P.BitwiseOperator_BitMask_n
	  section.data(5).logicalSrcIdx = 34;
	  section.data(5).dtTransOffset = 4;
	
	  ;% r_P.BitwiseOperator_BitMask_l
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
    ;% Auto data (r_B)
    ;%
      section.nData     = 33;
      section.data(33)  = dumData; %prealloc
      
	  ;% r_B.PacketInput_o3
	  section.data(1).logicalSrcIdx = 0;
	  section.data(1).dtTransOffset = 0;
	
	  ;% r_B.PacketInput_o4
	  section.data(2).logicalSrcIdx = 1;
	  section.data(2).dtTransOffset = 2;
	
	  ;% r_B.PacketInput_o5
	  section.data(3).logicalSrcIdx = 2;
	  section.data(3).dtTransOffset = 9;
	
	  ;% r_B.PacketInput_o6
	  section.data(4).logicalSrcIdx = 3;
	  section.data(4).dtTransOffset = 15;
	
	  ;% r_B.RateTransition3
	  section.data(5).logicalSrcIdx = 4;
	  section.data(5).dtTransOffset = 23;
	
	  ;% r_B.RateTransition4
	  section.data(6).logicalSrcIdx = 5;
	  section.data(6).dtTransOffset = 25;
	
	  ;% r_B.RateTransition5
	  section.data(7).logicalSrcIdx = 6;
	  section.data(7).dtTransOffset = 32;
	
	  ;% r_B.RateTransition6
	  section.data(8).logicalSrcIdx = 7;
	  section.data(8).dtTransOffset = 38;
	
	  ;% r_B.DataTypeConversion
	  section.data(9).logicalSrcIdx = 8;
	  section.data(9).dtTransOffset = 46;
	
	  ;% r_B.DerivativeGain
	  section.data(10).logicalSrcIdx = 9;
	  section.data(10).dtTransOffset = 47;
	
	  ;% r_B.FilterCoefficient
	  section.data(11).logicalSrcIdx = 10;
	  section.data(11).dtTransOffset = 48;
	
	  ;% r_B.IntegralGain
	  section.data(12).logicalSrcIdx = 11;
	  section.data(12).dtTransOffset = 49;
	
	  ;% r_B.ProportionalGain
	  section.data(13).logicalSrcIdx = 12;
	  section.data(13).dtTransOffset = 50;
	
	  ;% r_B.Switch
	  section.data(14).logicalSrcIdx = 13;
	  section.data(14).dtTransOffset = 51;
	
	  ;% r_B.DataTypeConversion_f
	  section.data(15).logicalSrcIdx = 14;
	  section.data(15).dtTransOffset = 52;
	
	  ;% r_B.DerivativeGain_f
	  section.data(16).logicalSrcIdx = 15;
	  section.data(16).dtTransOffset = 53;
	
	  ;% r_B.FilterCoefficient_k
	  section.data(17).logicalSrcIdx = 16;
	  section.data(17).dtTransOffset = 54;
	
	  ;% r_B.IntegralGain_j
	  section.data(18).logicalSrcIdx = 17;
	  section.data(18).dtTransOffset = 55;
	
	  ;% r_B.ProportionalGain_c
	  section.data(19).logicalSrcIdx = 18;
	  section.data(19).dtTransOffset = 56;
	
	  ;% r_B.Switch_f
	  section.data(20).logicalSrcIdx = 19;
	  section.data(20).dtTransOffset = 57;
	
	  ;% r_B.Sum
	  section.data(21).logicalSrcIdx = 20;
	  section.data(21).dtTransOffset = 58;
	
	  ;% r_B.DataTypeConversion_j
	  section.data(22).logicalSrcIdx = 21;
	  section.data(22).dtTransOffset = 59;
	
	  ;% r_B.DerivativeGain_j
	  section.data(23).logicalSrcIdx = 22;
	  section.data(23).dtTransOffset = 60;
	
	  ;% r_B.FilterCoefficient_j
	  section.data(24).logicalSrcIdx = 23;
	  section.data(24).dtTransOffset = 61;
	
	  ;% r_B.IntegralGain_d
	  section.data(25).logicalSrcIdx = 24;
	  section.data(25).dtTransOffset = 62;
	
	  ;% r_B.ProportionalGain_l
	  section.data(26).logicalSrcIdx = 25;
	  section.data(26).dtTransOffset = 63;
	
	  ;% r_B.Switch_n
	  section.data(27).logicalSrcIdx = 26;
	  section.data(27).dtTransOffset = 64;
	
	  ;% r_B.DataTypeConversion_c
	  section.data(28).logicalSrcIdx = 27;
	  section.data(28).dtTransOffset = 65;
	
	  ;% r_B.DerivativeGain_ff
	  section.data(29).logicalSrcIdx = 28;
	  section.data(29).dtTransOffset = 66;
	
	  ;% r_B.FilterCoefficient_h
	  section.data(30).logicalSrcIdx = 29;
	  section.data(30).dtTransOffset = 67;
	
	  ;% r_B.IntegralGain_o
	  section.data(31).logicalSrcIdx = 30;
	  section.data(31).dtTransOffset = 68;
	
	  ;% r_B.ProportionalGain_g
	  section.data(32).logicalSrcIdx = 31;
	  section.data(32).dtTransOffset = 69;
	
	  ;% r_B.Switch_m
	  section.data(33).logicalSrcIdx = 32;
	  section.data(33).dtTransOffset = 70;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(1) = section;
      clear section
      
      section.nData     = 3;
      section.data(3)  = dumData; %prealloc
      
	  ;% r_B.PacketInput_o1
	  section.data(1).logicalSrcIdx = 33;
	  section.data(1).dtTransOffset = 0;
	
	  ;% r_B.PacketInput_o2
	  section.data(2).logicalSrcIdx = 34;
	  section.data(2).dtTransOffset = 1;
	
	  ;% r_B.RateTransition2
	  section.data(3).logicalSrcIdx = 35;
	  section.data(3).dtTransOffset = 2;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(2) = section;
      clear section
      
      section.nData     = 4;
      section.data(4)  = dumData; %prealloc
      
	  ;% r_B.LogicalOperator
	  section.data(1).logicalSrcIdx = 36;
	  section.data(1).dtTransOffset = 0;
	
	  ;% r_B.LogicalOperator_d
	  section.data(2).logicalSrcIdx = 37;
	  section.data(2).dtTransOffset = 1;
	
	  ;% r_B.LogicalOperator_g
	  section.data(3).logicalSrcIdx = 38;
	  section.data(3).dtTransOffset = 2;
	
	  ;% r_B.LogicalOperator_l
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
    ;% Auto data (r_DWork)
    ;%
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% r_DWork.Scope_PWORK.LoggedData
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


  targMap.checksum0 = 2146525147;
  targMap.checksum1 = 114594147;
  targMap.checksum2 = 3439338169;
  targMap.checksum3 = 2421275999;

