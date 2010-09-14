/*

Copyright (C) 2010  Gaetan Guidet

This file is part of ofxpp.

ofxpp is free software; you can redistribute it and/or modify it
under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation; either version 2.1 of the License, or (at
your option) any later version.

ofxpp is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301,
USA.

*/

#ifndef __pyofx_macros_h__
#define __pyofx_macros_h__

#define MCR_EXPAND(x) x

#define MCR_CONCAT(x, y) MCR_CONCAT_(x, y)
#define MCR_CONCAT_(x, y) x ## y

#define MCR_STR(x) MCR_STR_(x)
#define MCR_STR_(x) #x

#define MCR_INCR_0 1
#define MCR_INCR_1 2
#define MCR_INCR_2 3
#define MCR_INCR_3 4
#define MCR_INCR_4 5
#define MCR_INCR_5 6
#define MCR_INCR_6 7
#define MCR_INCR_7 8
#define MCR_INCR_8 9
#define MCR_INCR_9 10
#define MCR_INCR_10 11
#define MCR_INCR_11 12
#define MCR_INCR_12 13
#define MCR_INCR_13 14
#define MCR_INCR_14 15
#define MCR_INCR_15 16
#define MCR_INCR_16 17
#define MCR_INCR_17 18
#define MCR_INCR_18 19
#define MCR_INCR_19 20
#define MCR_INCR_20 21
#define MCR_INCR_21 22
#define MCR_INCR_22 23
#define MCR_INCR_23 24
#define MCR_INCR_24 25
#define MCR_INCR_25 26
#define MCR_INCR_26 27
#define MCR_INCR_27 28
#define MCR_INCR_28 29
#define MCR_INCR_29 30
#define MCR_INCR_30 31
#define MCR_INCR_31 32
#define MCR_INCR_32 33
#define MCR_INCR_33 34
#define MCR_INCR_34 35
#define MCR_INCR_35 36
#define MCR_INCR_36 37
#define MCR_INCR_37 38
#define MCR_INCR_38 39
#define MCR_INCR_39 40
#define MCR_INCR_40 41
#define MCR_INCR_41 42
#define MCR_INCR_42 43
#define MCR_INCR_43 44
#define MCR_INCR_44 45
#define MCR_INCR_45 46
#define MCR_INCR_46 47
#define MCR_INCR_47 48
#define MCR_INCR_48 49
#define MCR_INCR_49 50
#define MCR_INCR_50 51
#define MCR_INCR_51 52
#define MCR_INCR_52 53
#define MCR_INCR_53 54
#define MCR_INCR_54 55
#define MCR_INCR_55 56
#define MCR_INCR_56 57
#define MCR_INCR_57 58
#define MCR_INCR_58 59
#define MCR_INCR_59 60
#define MCR_INCR_60 61
#define MCR_INCR_61 62
#define MCR_INCR_62 63
#define MCR_INCR_63 64
#define MCR_INCR_64 65
#define MCR_INCR_65 66
#define MCR_INCR_66 67
#define MCR_INCR_67 68
#define MCR_INCR_68 69
#define MCR_INCR_69 70
#define MCR_INCR_70 71
#define MCR_INCR_71 72
#define MCR_INCR_72 73
#define MCR_INCR_73 74
#define MCR_INCR_74 75
#define MCR_INCR_75 76
#define MCR_INCR_76 77
#define MCR_INCR_77 78
#define MCR_INCR_78 79
#define MCR_INCR_79 80
#define MCR_INCR_80 81
#define MCR_INCR_81 82
#define MCR_INCR_82 83
#define MCR_INCR_83 84
#define MCR_INCR_84 85
#define MCR_INCR_85 86
#define MCR_INCR_86 87
#define MCR_INCR_87 88
#define MCR_INCR_88 89
#define MCR_INCR_89 90
#define MCR_INCR_90 91
#define MCR_INCR_91 92
#define MCR_INCR_92 93
#define MCR_INCR_93 94
#define MCR_INCR_94 95
#define MCR_INCR_95 96
#define MCR_INCR_96 97
#define MCR_INCR_97 98
#define MCR_INCR_98 99
#define MCR_INCR_99 100
#define MCR_INCR_100 101
#define MCR_INCR_101 102
#define MCR_INCR_102 103
#define MCR_INCR_103 104
#define MCR_INCR_104 105
#define MCR_INCR_105 106
#define MCR_INCR_106 107
#define MCR_INCR_107 108
#define MCR_INCR_108 109
#define MCR_INCR_109 110
#define MCR_INCR_110 111
#define MCR_INCR_111 112
#define MCR_INCR_112 113
#define MCR_INCR_113 114
#define MCR_INCR_114 115
#define MCR_INCR_115 116
#define MCR_INCR_116 117
#define MCR_INCR_117 118
#define MCR_INCR_118 119
#define MCR_INCR_119 120
#define MCR_INCR_120 121
#define MCR_INCR_121 122
#define MCR_INCR_122 123
#define MCR_INCR_123 124
#define MCR_INCR_124 125
#define MCR_INCR_125 126
#define MCR_INCR_126 127
#define MCR_INCR_127 128
#define MCR_INCR_128 129
#define MCR_INCR(n) MCR_CONCAT(MCR_INCR_, n)

#define MCR_DECR_0 
#define MCR_DECR_1 0
#define MCR_DECR_2 1
#define MCR_DECR_3 2
#define MCR_DECR_4 3
#define MCR_DECR_5 4
#define MCR_DECR_6 5
#define MCR_DECR_7 6
#define MCR_DECR_8 7
#define MCR_DECR_9 8
#define MCR_DECR_10 9
#define MCR_DECR_11 10
#define MCR_DECR_12 11
#define MCR_DECR_13 12
#define MCR_DECR_14 13
#define MCR_DECR_15 14
#define MCR_DECR_16 15
#define MCR_DECR_17 16
#define MCR_DECR_18 17
#define MCR_DECR_19 18
#define MCR_DECR_20 19
#define MCR_DECR_21 20
#define MCR_DECR_22 21
#define MCR_DECR_23 22
#define MCR_DECR_24 23
#define MCR_DECR_25 24
#define MCR_DECR_26 25
#define MCR_DECR_27 26
#define MCR_DECR_28 27
#define MCR_DECR_29 28
#define MCR_DECR_30 29
#define MCR_DECR_31 30
#define MCR_DECR_32 31
#define MCR_DECR_33 32
#define MCR_DECR_34 33
#define MCR_DECR_35 34
#define MCR_DECR_36 35
#define MCR_DECR_37 36
#define MCR_DECR_38 37
#define MCR_DECR_39 38
#define MCR_DECR_40 39
#define MCR_DECR_41 40
#define MCR_DECR_42 41
#define MCR_DECR_43 42
#define MCR_DECR_44 43
#define MCR_DECR_45 44
#define MCR_DECR_46 45
#define MCR_DECR_47 46
#define MCR_DECR_48 47
#define MCR_DECR_49 48
#define MCR_DECR_50 49
#define MCR_DECR_51 50
#define MCR_DECR_52 51
#define MCR_DECR_53 52
#define MCR_DECR_54 53
#define MCR_DECR_55 54
#define MCR_DECR_56 55
#define MCR_DECR_57 56
#define MCR_DECR_58 57
#define MCR_DECR_59 58
#define MCR_DECR_60 59
#define MCR_DECR_61 60
#define MCR_DECR_62 61
#define MCR_DECR_63 62
#define MCR_DECR_64 63
#define MCR_DECR_65 64
#define MCR_DECR_66 65
#define MCR_DECR_67 66
#define MCR_DECR_68 67
#define MCR_DECR_69 68
#define MCR_DECR_70 69
#define MCR_DECR_71 70
#define MCR_DECR_72 71
#define MCR_DECR_73 72
#define MCR_DECR_74 73
#define MCR_DECR_75 74
#define MCR_DECR_76 75
#define MCR_DECR_77 76
#define MCR_DECR_78 77
#define MCR_DECR_79 78
#define MCR_DECR_80 79
#define MCR_DECR_81 80
#define MCR_DECR_82 81
#define MCR_DECR_83 82
#define MCR_DECR_84 83
#define MCR_DECR_85 84
#define MCR_DECR_86 85
#define MCR_DECR_87 86
#define MCR_DECR_88 87
#define MCR_DECR_89 88
#define MCR_DECR_90 89
#define MCR_DECR_91 90
#define MCR_DECR_92 91
#define MCR_DECR_93 92
#define MCR_DECR_94 93
#define MCR_DECR_95 94
#define MCR_DECR_96 95
#define MCR_DECR_97 96
#define MCR_DECR_98 97
#define MCR_DECR_99 98
#define MCR_DECR_100 99
#define MCR_DECR_101 100
#define MCR_DECR_102 101
#define MCR_DECR_103 102
#define MCR_DECR_104 103
#define MCR_DECR_105 104
#define MCR_DECR_106 105
#define MCR_DECR_107 106
#define MCR_DECR_108 107
#define MCR_DECR_109 108
#define MCR_DECR_110 109
#define MCR_DECR_111 110
#define MCR_DECR_112 111
#define MCR_DECR_113 112
#define MCR_DECR_114 113
#define MCR_DECR_115 114
#define MCR_DECR_116 115
#define MCR_DECR_117 116
#define MCR_DECR_118 117
#define MCR_DECR_119 118
#define MCR_DECR_120 119
#define MCR_DECR_121 120
#define MCR_DECR_122 121
#define MCR_DECR_123 122
#define MCR_DECR_124 123
#define MCR_DECR_125 124
#define MCR_DECR_126 125
#define MCR_DECR_127 126
#define MCR_DECR_128 127
#define MCR_DECR(n) MCR_CONCAT(MCR_DECR_, n)

#define MCR_REP_0(macro, p0, p1, p2, p3) 
#define MCR_REP_1(macro, p0, p1, p2, p3) macro(0, p0, p1, p2, p3)
#define MCR_REP_2(macro, p0, p1, p2, p3) MCR_REP_1(macro, p0, p1, p2, p3) macro(1, p0, p1, p2, p3)
#define MCR_REP_3(macro, p0, p1, p2, p3) MCR_REP_2(macro, p0, p1, p2, p3) macro(2, p0, p1, p2, p3)
#define MCR_REP_4(macro, p0, p1, p2, p3) MCR_REP_3(macro, p0, p1, p2, p3) macro(3, p0, p1, p2, p3)
#define MCR_REP_5(macro, p0, p1, p2, p3) MCR_REP_4(macro, p0, p1, p2, p3) macro(4, p0, p1, p2, p3)
#define MCR_REP_6(macro, p0, p1, p2, p3) MCR_REP_5(macro, p0, p1, p2, p3) macro(5, p0, p1, p2, p3)
#define MCR_REP_7(macro, p0, p1, p2, p3) MCR_REP_6(macro, p0, p1, p2, p3) macro(6, p0, p1, p2, p3)
#define MCR_REP_8(macro, p0, p1, p2, p3) MCR_REP_7(macro, p0, p1, p2, p3) macro(7, p0, p1, p2, p3)
#define MCR_REP_9(macro, p0, p1, p2, p3) MCR_REP_8(macro, p0, p1, p2, p3) macro(8, p0, p1, p2, p3)
#define MCR_REP_10(macro, p0, p1, p2, p3) MCR_REP_9(macro, p0, p1, p2, p3) macro(9, p0, p1, p2, p3)
#define MCR_REP_11(macro, p0, p1, p2, p3) MCR_REP_10(macro, p0, p1, p2, p3) macro(10, p0, p1, p2, p3)
#define MCR_REP_12(macro, p0, p1, p2, p3) MCR_REP_11(macro, p0, p1, p2, p3) macro(11, p0, p1, p2, p3)
#define MCR_REP_13(macro, p0, p1, p2, p3) MCR_REP_12(macro, p0, p1, p2, p3) macro(12, p0, p1, p2, p3)
#define MCR_REP_14(macro, p0, p1, p2, p3) MCR_REP_13(macro, p0, p1, p2, p3) macro(13, p0, p1, p2, p3)
#define MCR_REP_15(macro, p0, p1, p2, p3) MCR_REP_14(macro, p0, p1, p2, p3) macro(14, p0, p1, p2, p3)
#define MCR_REP_16(macro, p0, p1, p2, p3) MCR_REP_15(macro, p0, p1, p2, p3) macro(15, p0, p1, p2, p3)
#define MCR_REP_17(macro, p0, p1, p2, p3) MCR_REP_16(macro, p0, p1, p2, p3) macro(16, p0, p1, p2, p3)
#define MCR_REP_18(macro, p0, p1, p2, p3) MCR_REP_17(macro, p0, p1, p2, p3) macro(17, p0, p1, p2, p3)
#define MCR_REP_19(macro, p0, p1, p2, p3) MCR_REP_18(macro, p0, p1, p2, p3) macro(18, p0, p1, p2, p3)
#define MCR_REP_20(macro, p0, p1, p2, p3) MCR_REP_19(macro, p0, p1, p2, p3) macro(19, p0, p1, p2, p3)
#define MCR_REP_21(macro, p0, p1, p2, p3) MCR_REP_20(macro, p0, p1, p2, p3) macro(20, p0, p1, p2, p3)
#define MCR_REP_22(macro, p0, p1, p2, p3) MCR_REP_21(macro, p0, p1, p2, p3) macro(21, p0, p1, p2, p3)
#define MCR_REP_23(macro, p0, p1, p2, p3) MCR_REP_22(macro, p0, p1, p2, p3) macro(22, p0, p1, p2, p3)
#define MCR_REP_24(macro, p0, p1, p2, p3) MCR_REP_23(macro, p0, p1, p2, p3) macro(23, p0, p1, p2, p3)
#define MCR_REP_25(macro, p0, p1, p2, p3) MCR_REP_24(macro, p0, p1, p2, p3) macro(24, p0, p1, p2, p3)
#define MCR_REP_26(macro, p0, p1, p2, p3) MCR_REP_25(macro, p0, p1, p2, p3) macro(25, p0, p1, p2, p3)
#define MCR_REP_27(macro, p0, p1, p2, p3) MCR_REP_26(macro, p0, p1, p2, p3) macro(26, p0, p1, p2, p3)
#define MCR_REP_28(macro, p0, p1, p2, p3) MCR_REP_27(macro, p0, p1, p2, p3) macro(27, p0, p1, p2, p3)
#define MCR_REP_29(macro, p0, p1, p2, p3) MCR_REP_28(macro, p0, p1, p2, p3) macro(28, p0, p1, p2, p3)
#define MCR_REP_30(macro, p0, p1, p2, p3) MCR_REP_29(macro, p0, p1, p2, p3) macro(29, p0, p1, p2, p3)
#define MCR_REP_31(macro, p0, p1, p2, p3) MCR_REP_30(macro, p0, p1, p2, p3) macro(30, p0, p1, p2, p3)
#define MCR_REP_32(macro, p0, p1, p2, p3) MCR_REP_31(macro, p0, p1, p2, p3) macro(31, p0, p1, p2, p3)
#define MCR_REP_33(macro, p0, p1, p2, p3) MCR_REP_32(macro, p0, p1, p2, p3) macro(32, p0, p1, p2, p3)
#define MCR_REP_34(macro, p0, p1, p2, p3) MCR_REP_33(macro, p0, p1, p2, p3) macro(33, p0, p1, p2, p3)
#define MCR_REP_35(macro, p0, p1, p2, p3) MCR_REP_34(macro, p0, p1, p2, p3) macro(34, p0, p1, p2, p3)
#define MCR_REP_36(macro, p0, p1, p2, p3) MCR_REP_35(macro, p0, p1, p2, p3) macro(35, p0, p1, p2, p3)
#define MCR_REP_37(macro, p0, p1, p2, p3) MCR_REP_36(macro, p0, p1, p2, p3) macro(36, p0, p1, p2, p3)
#define MCR_REP_38(macro, p0, p1, p2, p3) MCR_REP_37(macro, p0, p1, p2, p3) macro(37, p0, p1, p2, p3)
#define MCR_REP_39(macro, p0, p1, p2, p3) MCR_REP_38(macro, p0, p1, p2, p3) macro(38, p0, p1, p2, p3)
#define MCR_REP_40(macro, p0, p1, p2, p3) MCR_REP_39(macro, p0, p1, p2, p3) macro(39, p0, p1, p2, p3)
#define MCR_REP_41(macro, p0, p1, p2, p3) MCR_REP_40(macro, p0, p1, p2, p3) macro(40, p0, p1, p2, p3)
#define MCR_REP_42(macro, p0, p1, p2, p3) MCR_REP_41(macro, p0, p1, p2, p3) macro(41, p0, p1, p2, p3)
#define MCR_REP_43(macro, p0, p1, p2, p3) MCR_REP_42(macro, p0, p1, p2, p3) macro(42, p0, p1, p2, p3)
#define MCR_REP_44(macro, p0, p1, p2, p3) MCR_REP_43(macro, p0, p1, p2, p3) macro(43, p0, p1, p2, p3)
#define MCR_REP_45(macro, p0, p1, p2, p3) MCR_REP_44(macro, p0, p1, p2, p3) macro(44, p0, p1, p2, p3)
#define MCR_REP_46(macro, p0, p1, p2, p3) MCR_REP_45(macro, p0, p1, p2, p3) macro(45, p0, p1, p2, p3)
#define MCR_REP_47(macro, p0, p1, p2, p3) MCR_REP_46(macro, p0, p1, p2, p3) macro(46, p0, p1, p2, p3)
#define MCR_REP_48(macro, p0, p1, p2, p3) MCR_REP_47(macro, p0, p1, p2, p3) macro(47, p0, p1, p2, p3)
#define MCR_REP_49(macro, p0, p1, p2, p3) MCR_REP_48(macro, p0, p1, p2, p3) macro(48, p0, p1, p2, p3)
#define MCR_REP_50(macro, p0, p1, p2, p3) MCR_REP_49(macro, p0, p1, p2, p3) macro(49, p0, p1, p2, p3)
#define MCR_REP_51(macro, p0, p1, p2, p3) MCR_REP_50(macro, p0, p1, p2, p3) macro(50, p0, p1, p2, p3)
#define MCR_REP_52(macro, p0, p1, p2, p3) MCR_REP_51(macro, p0, p1, p2, p3) macro(51, p0, p1, p2, p3)
#define MCR_REP_53(macro, p0, p1, p2, p3) MCR_REP_52(macro, p0, p1, p2, p3) macro(52, p0, p1, p2, p3)
#define MCR_REP_54(macro, p0, p1, p2, p3) MCR_REP_53(macro, p0, p1, p2, p3) macro(53, p0, p1, p2, p3)
#define MCR_REP_55(macro, p0, p1, p2, p3) MCR_REP_54(macro, p0, p1, p2, p3) macro(54, p0, p1, p2, p3)
#define MCR_REP_56(macro, p0, p1, p2, p3) MCR_REP_55(macro, p0, p1, p2, p3) macro(55, p0, p1, p2, p3)
#define MCR_REP_57(macro, p0, p1, p2, p3) MCR_REP_56(macro, p0, p1, p2, p3) macro(56, p0, p1, p2, p3)
#define MCR_REP_58(macro, p0, p1, p2, p3) MCR_REP_57(macro, p0, p1, p2, p3) macro(57, p0, p1, p2, p3)
#define MCR_REP_59(macro, p0, p1, p2, p3) MCR_REP_58(macro, p0, p1, p2, p3) macro(58, p0, p1, p2, p3)
#define MCR_REP_60(macro, p0, p1, p2, p3) MCR_REP_59(macro, p0, p1, p2, p3) macro(59, p0, p1, p2, p3)
#define MCR_REP_61(macro, p0, p1, p2, p3) MCR_REP_60(macro, p0, p1, p2, p3) macro(60, p0, p1, p2, p3)
#define MCR_REP_62(macro, p0, p1, p2, p3) MCR_REP_61(macro, p0, p1, p2, p3) macro(61, p0, p1, p2, p3)
#define MCR_REP_63(macro, p0, p1, p2, p3) MCR_REP_62(macro, p0, p1, p2, p3) macro(62, p0, p1, p2, p3)
#define MCR_REP_64(macro, p0, p1, p2, p3) MCR_REP_63(macro, p0, p1, p2, p3) macro(63, p0, p1, p2, p3)
#define MCR_REP_65(macro, p0, p1, p2, p3) MCR_REP_64(macro, p0, p1, p2, p3) macro(64, p0, p1, p2, p3)
#define MCR_REP_66(macro, p0, p1, p2, p3) MCR_REP_65(macro, p0, p1, p2, p3) macro(65, p0, p1, p2, p3)
#define MCR_REP_67(macro, p0, p1, p2, p3) MCR_REP_66(macro, p0, p1, p2, p3) macro(66, p0, p1, p2, p3)
#define MCR_REP_68(macro, p0, p1, p2, p3) MCR_REP_67(macro, p0, p1, p2, p3) macro(67, p0, p1, p2, p3)
#define MCR_REP_69(macro, p0, p1, p2, p3) MCR_REP_68(macro, p0, p1, p2, p3) macro(68, p0, p1, p2, p3)
#define MCR_REP_70(macro, p0, p1, p2, p3) MCR_REP_69(macro, p0, p1, p2, p3) macro(69, p0, p1, p2, p3)
#define MCR_REP_71(macro, p0, p1, p2, p3) MCR_REP_70(macro, p0, p1, p2, p3) macro(70, p0, p1, p2, p3)
#define MCR_REP_72(macro, p0, p1, p2, p3) MCR_REP_71(macro, p0, p1, p2, p3) macro(71, p0, p1, p2, p3)
#define MCR_REP_73(macro, p0, p1, p2, p3) MCR_REP_72(macro, p0, p1, p2, p3) macro(72, p0, p1, p2, p3)
#define MCR_REP_74(macro, p0, p1, p2, p3) MCR_REP_73(macro, p0, p1, p2, p3) macro(73, p0, p1, p2, p3)
#define MCR_REP_75(macro, p0, p1, p2, p3) MCR_REP_74(macro, p0, p1, p2, p3) macro(74, p0, p1, p2, p3)
#define MCR_REP_76(macro, p0, p1, p2, p3) MCR_REP_75(macro, p0, p1, p2, p3) macro(75, p0, p1, p2, p3)
#define MCR_REP_77(macro, p0, p1, p2, p3) MCR_REP_76(macro, p0, p1, p2, p3) macro(76, p0, p1, p2, p3)
#define MCR_REP_78(macro, p0, p1, p2, p3) MCR_REP_77(macro, p0, p1, p2, p3) macro(77, p0, p1, p2, p3)
#define MCR_REP_79(macro, p0, p1, p2, p3) MCR_REP_78(macro, p0, p1, p2, p3) macro(78, p0, p1, p2, p3)
#define MCR_REP_80(macro, p0, p1, p2, p3) MCR_REP_79(macro, p0, p1, p2, p3) macro(79, p0, p1, p2, p3)
#define MCR_REP_81(macro, p0, p1, p2, p3) MCR_REP_80(macro, p0, p1, p2, p3) macro(80, p0, p1, p2, p3)
#define MCR_REP_82(macro, p0, p1, p2, p3) MCR_REP_81(macro, p0, p1, p2, p3) macro(81, p0, p1, p2, p3)
#define MCR_REP_83(macro, p0, p1, p2, p3) MCR_REP_82(macro, p0, p1, p2, p3) macro(82, p0, p1, p2, p3)
#define MCR_REP_84(macro, p0, p1, p2, p3) MCR_REP_83(macro, p0, p1, p2, p3) macro(83, p0, p1, p2, p3)
#define MCR_REP_85(macro, p0, p1, p2, p3) MCR_REP_84(macro, p0, p1, p2, p3) macro(84, p0, p1, p2, p3)
#define MCR_REP_86(macro, p0, p1, p2, p3) MCR_REP_85(macro, p0, p1, p2, p3) macro(85, p0, p1, p2, p3)
#define MCR_REP_87(macro, p0, p1, p2, p3) MCR_REP_86(macro, p0, p1, p2, p3) macro(86, p0, p1, p2, p3)
#define MCR_REP_88(macro, p0, p1, p2, p3) MCR_REP_87(macro, p0, p1, p2, p3) macro(87, p0, p1, p2, p3)
#define MCR_REP_89(macro, p0, p1, p2, p3) MCR_REP_88(macro, p0, p1, p2, p3) macro(88, p0, p1, p2, p3)
#define MCR_REP_90(macro, p0, p1, p2, p3) MCR_REP_89(macro, p0, p1, p2, p3) macro(89, p0, p1, p2, p3)
#define MCR_REP_91(macro, p0, p1, p2, p3) MCR_REP_90(macro, p0, p1, p2, p3) macro(90, p0, p1, p2, p3)
#define MCR_REP_92(macro, p0, p1, p2, p3) MCR_REP_91(macro, p0, p1, p2, p3) macro(91, p0, p1, p2, p3)
#define MCR_REP_93(macro, p0, p1, p2, p3) MCR_REP_92(macro, p0, p1, p2, p3) macro(92, p0, p1, p2, p3)
#define MCR_REP_94(macro, p0, p1, p2, p3) MCR_REP_93(macro, p0, p1, p2, p3) macro(93, p0, p1, p2, p3)
#define MCR_REP_95(macro, p0, p1, p2, p3) MCR_REP_94(macro, p0, p1, p2, p3) macro(94, p0, p1, p2, p3)
#define MCR_REP_96(macro, p0, p1, p2, p3) MCR_REP_95(macro, p0, p1, p2, p3) macro(95, p0, p1, p2, p3)
#define MCR_REP_97(macro, p0, p1, p2, p3) MCR_REP_96(macro, p0, p1, p2, p3) macro(96, p0, p1, p2, p3)
#define MCR_REP_98(macro, p0, p1, p2, p3) MCR_REP_97(macro, p0, p1, p2, p3) macro(97, p0, p1, p2, p3)
#define MCR_REP_99(macro, p0, p1, p2, p3) MCR_REP_98(macro, p0, p1, p2, p3) macro(98, p0, p1, p2, p3)
#define MCR_REP_100(macro, p0, p1, p2, p3) MCR_REP_99(macro, p0, p1, p2, p3) macro(99, p0, p1, p2, p3)
#define MCR_REP_101(macro, p0, p1, p2, p3) MCR_REP_100(macro, p0, p1, p2, p3) macro(100, p0, p1, p2, p3)
#define MCR_REP_102(macro, p0, p1, p2, p3) MCR_REP_101(macro, p0, p1, p2, p3) macro(101, p0, p1, p2, p3)
#define MCR_REP_103(macro, p0, p1, p2, p3) MCR_REP_102(macro, p0, p1, p2, p3) macro(102, p0, p1, p2, p3)
#define MCR_REP_104(macro, p0, p1, p2, p3) MCR_REP_103(macro, p0, p1, p2, p3) macro(103, p0, p1, p2, p3)
#define MCR_REP_105(macro, p0, p1, p2, p3) MCR_REP_104(macro, p0, p1, p2, p3) macro(104, p0, p1, p2, p3)
#define MCR_REP_106(macro, p0, p1, p2, p3) MCR_REP_105(macro, p0, p1, p2, p3) macro(105, p0, p1, p2, p3)
#define MCR_REP_107(macro, p0, p1, p2, p3) MCR_REP_106(macro, p0, p1, p2, p3) macro(106, p0, p1, p2, p3)
#define MCR_REP_108(macro, p0, p1, p2, p3) MCR_REP_107(macro, p0, p1, p2, p3) macro(107, p0, p1, p2, p3)
#define MCR_REP_109(macro, p0, p1, p2, p3) MCR_REP_108(macro, p0, p1, p2, p3) macro(108, p0, p1, p2, p3)
#define MCR_REP_110(macro, p0, p1, p2, p3) MCR_REP_109(macro, p0, p1, p2, p3) macro(109, p0, p1, p2, p3)
#define MCR_REP_111(macro, p0, p1, p2, p3) MCR_REP_110(macro, p0, p1, p2, p3) macro(110, p0, p1, p2, p3)
#define MCR_REP_112(macro, p0, p1, p2, p3) MCR_REP_111(macro, p0, p1, p2, p3) macro(111, p0, p1, p2, p3)
#define MCR_REP_113(macro, p0, p1, p2, p3) MCR_REP_112(macro, p0, p1, p2, p3) macro(112, p0, p1, p2, p3)
#define MCR_REP_114(macro, p0, p1, p2, p3) MCR_REP_113(macro, p0, p1, p2, p3) macro(113, p0, p1, p2, p3)
#define MCR_REP_115(macro, p0, p1, p2, p3) MCR_REP_114(macro, p0, p1, p2, p3) macro(114, p0, p1, p2, p3)
#define MCR_REP_116(macro, p0, p1, p2, p3) MCR_REP_115(macro, p0, p1, p2, p3) macro(115, p0, p1, p2, p3)
#define MCR_REP_117(macro, p0, p1, p2, p3) MCR_REP_116(macro, p0, p1, p2, p3) macro(116, p0, p1, p2, p3)
#define MCR_REP_118(macro, p0, p1, p2, p3) MCR_REP_117(macro, p0, p1, p2, p3) macro(117, p0, p1, p2, p3)
#define MCR_REP_119(macro, p0, p1, p2, p3) MCR_REP_118(macro, p0, p1, p2, p3) macro(118, p0, p1, p2, p3)
#define MCR_REP_120(macro, p0, p1, p2, p3) MCR_REP_119(macro, p0, p1, p2, p3) macro(119, p0, p1, p2, p3)
#define MCR_REP_121(macro, p0, p1, p2, p3) MCR_REP_120(macro, p0, p1, p2, p3) macro(120, p0, p1, p2, p3)
#define MCR_REP_122(macro, p0, p1, p2, p3) MCR_REP_121(macro, p0, p1, p2, p3) macro(121, p0, p1, p2, p3)
#define MCR_REP_123(macro, p0, p1, p2, p3) MCR_REP_122(macro, p0, p1, p2, p3) macro(122, p0, p1, p2, p3)
#define MCR_REP_124(macro, p0, p1, p2, p3) MCR_REP_123(macro, p0, p1, p2, p3) macro(123, p0, p1, p2, p3)
#define MCR_REP_125(macro, p0, p1, p2, p3) MCR_REP_124(macro, p0, p1, p2, p3) macro(124, p0, p1, p2, p3)
#define MCR_REP_126(macro, p0, p1, p2, p3) MCR_REP_125(macro, p0, p1, p2, p3) macro(125, p0, p1, p2, p3)
#define MCR_REP_127(macro, p0, p1, p2, p3) MCR_REP_126(macro, p0, p1, p2, p3) macro(126, p0, p1, p2, p3)
#define MCR_REP_128(macro, p0, p1, p2, p3) MCR_REP_127(macro, p0, p1, p2, p3) macro(127, p0, p1, p2, p3)

#define MCR_REP(N, MIDDLE, LAST, p0, p1, p2, p3) MCR_CONCAT(MCR_REP_, MCR_DECR(N))(MIDDLE, p0, p1, p2, p3) LAST(N, p0, p1, p2, p3)

#endif
