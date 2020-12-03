/////////////////////////////////////////////////////////////////////////////
//                                                                         //
//            FEDERAL UNIVERSITY OF RIO GRANDE DO NORTE - UFRN             //
//                   DIGITAL METROPOLIS INSTITUTE - IMD                    //
//                BACHELOR OF INFORMATION TECHNOLOGY - BTI                 //
//           SPECIAL TOPICS ON INTERNET OF THINGS "B" - IMD0291            //
//                                                                         //
/////////////////////////////////////////////////////////////////////////////
//                                                                         //
// Names: oddeven.h                                                        //
//        report.h                                                         //
//        report.pdf                                                       //
//        odd-even-transposition-sort-serial.cpp                           //
//        odd-even-transposition-sort-parallel.cpp                         //
//        calculates-serie-parallel-analysis.cpp                           //
//        shellscript_start.sh                                             //
//        README.txt                                                       //
// Date: 28/10/2020                                                        //
// Version: 1.0                                                            //
//                                                                         //
// Author: P.R.O.Lima                                                      //
//                                                                         //
// Repository: https://github.com/r4m0nl1m4/odd-even-transposition-sort    //
//                                                                         //
// Software: GNU Compiler Collection (gcc) 9.3.0                           //
//                                                                         //
/////////////////////////////////////////////////////////////////////////////
//                                                                         //
// Description: Simple  sorting  algorithm, developed for use on serie and //
// parallel  processors  with  local  interconnections. It is a comparison //
// sort related to bubble sort, with which it shares many characteristics. //
// It  functions  by  comparing  all  odd/even  indexed  pairs of adjacent //
// elements in the list and, if a pair is in the wrong order (the first is //
// larger  than  the  second)  the  elements  are  switched. The next step //
// repeats this for even/odd indexed pairs (of adjacent elements). Then it //
// alternates  between  odd/even  and  even/odd  steps  until  the list is //    
// sorted.                                                                 //
//                                                                         //
/////////////////////////////////////////////////////////////////////////////
//                                                                         //
// To execute:                                                             //
//     ~$ bash shellscript_start.sh                                        //
//                                                                         //
/////////////////////////////////////////////////////////////////////////////


