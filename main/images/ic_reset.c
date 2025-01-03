#ifdef __has_include
    #if __has_include("lvgl.h")
        #ifndef LV_LVGL_H_INCLUDE_SIMPLE
            #define LV_LVGL_H_INCLUDE_SIMPLE
        #endif
    #endif
#endif

#if defined(LV_LVGL_H_INCLUDE_SIMPLE)
    #include "lvgl.h"
#else
    #include "lvgl/lvgl.h"
#endif


#ifndef LV_ATTRIBUTE_MEM_ALIGN
#define LV_ATTRIBUTE_MEM_ALIGN
#endif

#ifndef LV_ATTRIBUTE_IMG_IC_RESET
#define LV_ATTRIBUTE_IMG_IC_RESET
#endif

const LV_ATTRIBUTE_MEM_ALIGN LV_ATTRIBUTE_LARGE_CONST LV_ATTRIBUTE_IMG_IC_RESET uint8_t ic_reset_map[] = {
  0x00, 0x00, 0x00, 0x00, 	/*Color of index 0*/
  0x7f, 0x7f, 0x00, 0x02, 	/*Color of index 1*/
  0xff, 0xcc, 0x33, 0x05, 	/*Color of index 2*/
  0xe3, 0xc6, 0x39, 0x09, 	/*Color of index 3*/
  0xe6, 0xb3, 0x33, 0x0a, 	/*Color of index 4*/
  0xe9, 0xbc, 0x2c, 0x0b, 	/*Color of index 5*/
  0xf2, 0xbc, 0x36, 0x13, 	/*Color of index 6*/
  0xf3, 0xc2, 0x31, 0x15, 	/*Color of index 7*/
  0xe8, 0xb9, 0x2e, 0x16, 	/*Color of index 8*/
  0xe9, 0xb1, 0x2c, 0x17, 	/*Color of index 9*/
  0xed, 0xbf, 0x2e, 0x1c, 	/*Color of index 10*/
  0xed, 0xb9, 0x35, 0x1d, 	/*Color of index 11*/
  0xeb, 0xbc, 0x2f, 0x26, 	/*Color of index 12*/
  0xe9, 0xb4, 0x2c, 0x24, 	/*Color of index 13*/
  0xeb, 0xb8, 0x2d, 0x27, 	/*Color of index 14*/
  0xee, 0xbb, 0x30, 0x2f, 	/*Color of index 15*/
  0xec, 0xb8, 0x2f, 0x36, 	/*Color of index 16*/
  0xed, 0xbc, 0x31, 0x39, 	/*Color of index 17*/
  0xeb, 0xb7, 0x30, 0x40, 	/*Color of index 18*/
  0xeb, 0xb5, 0x2b, 0x40, 	/*Color of index 19*/
  0xec, 0xbb, 0x2d, 0x44, 	/*Color of index 20*/
  0xee, 0xbd, 0x31, 0x5a, 	/*Color of index 21*/
  0xec, 0xb4, 0x2a, 0x53, 	/*Color of index 22*/
  0xec, 0xb5, 0x2c, 0x5d, 	/*Color of index 23*/
  0xeb, 0xb5, 0x2d, 0x67, 	/*Color of index 24*/
  0xea, 0xb4, 0x2a, 0x6d, 	/*Color of index 25*/
  0xed, 0xb9, 0x2e, 0x74, 	/*Color of index 26*/
  0xee, 0xbc, 0x32, 0x7a, 	/*Color of index 27*/
  0xeb, 0xb6, 0x2c, 0x73, 	/*Color of index 28*/
  0xec, 0xb7, 0x2e, 0x79, 	/*Color of index 29*/
  0xed, 0xb9, 0x2e, 0x7c, 	/*Color of index 30*/
  0xee, 0xbc, 0x32, 0x88, 	/*Color of index 31*/
  0xee, 0xbc, 0x31, 0x9a, 	/*Color of index 32*/
  0xed, 0xbb, 0x31, 0xaa, 	/*Color of index 33*/
  0xeb, 0xb8, 0x2e, 0xa8, 	/*Color of index 34*/
  0xf0, 0xbd, 0x32, 0xb6, 	/*Color of index 35*/
  0xed, 0xb9, 0x2d, 0xaf, 	/*Color of index 36*/
  0xee, 0xb9, 0x2e, 0xbe, 	/*Color of index 37*/
  0xeb, 0xb5, 0x2c, 0xbb, 	/*Color of index 38*/
  0xee, 0xb8, 0x2f, 0xc3, 	/*Color of index 39*/
  0xed, 0xba, 0x2f, 0xcc, 	/*Color of index 40*/
  0xea, 0xb5, 0x2b, 0xc3, 	/*Color of index 41*/
  0xee, 0xbc, 0x32, 0xd4, 	/*Color of index 42*/
  0xec, 0xb6, 0x2d, 0xcc, 	/*Color of index 43*/
  0xec, 0xb8, 0x2e, 0xd3, 	/*Color of index 44*/
  0xec, 0xb9, 0x30, 0xdc, 	/*Color of index 45*/
  0xee, 0xbb, 0x31, 0xe3, 	/*Color of index 46*/
  0xeb, 0xb8, 0x2f, 0xde, 	/*Color of index 47*/
  0xec, 0xb9, 0x2f, 0xe2, 	/*Color of index 48*/
  0xed, 0xbb, 0x30, 0xeb, 	/*Color of index 49*/
  0xeb, 0xb6, 0x2d, 0xed, 	/*Color of index 50*/
  0xed, 0xba, 0x2f, 0xf8, 	/*Color of index 51*/
  0xee, 0xbb, 0x30, 0xff, 	/*Color of index 52*/
  0xec, 0xb7, 0x2e, 0xfe, 	/*Color of index 53*/
  0xeb, 0xb3, 0x2b, 0xfe, 	/*Color of index 54*/
  0xff, 0xaa, 0x55, 0x03, 	/*Color of index 55*/
  0xff, 0x7f, 0x00, 0x02, 	/*Color of index 56*/
  0xff, 0xb6, 0x24, 0x07, 	/*Color of index 57*/
  0xbf, 0x40, 0x00, 0x04, 	/*Color of index 58*/
  0xd4, 0x7f, 0x00, 0x06, 	/*Color of index 59*/
  0xd4, 0x55, 0x00, 0x06, 	/*Color of index 60*/
  0xbf, 0x60, 0x00, 0x08, 	/*Color of index 61*/
  0xcc, 0x66, 0x1a, 0x0a, 	/*Color of index 62*/
  0xb3, 0x66, 0x00, 0x0a, 	/*Color of index 63*/
  0xd4, 0x6a, 0x00, 0x0c, 	/*Color of index 64*/
  0xf3, 0xb6, 0x31, 0x15, 	/*Color of index 65*/
  0xdb, 0x6d, 0x00, 0x0e, 	/*Color of index 66*/
  0xec, 0xb3, 0x2f, 0x1b, 	/*Color of index 67*/
  0xc3, 0x69, 0x0f, 0x11, 	/*Color of index 68*/
  0xd7, 0x6b, 0x00, 0x13, 	/*Color of index 69*/
  0xb3, 0x73, 0x0d, 0x14, 	/*Color of index 70*/
  0xb8, 0x55, 0x00, 0x12, 	/*Color of index 71*/
  0xbf, 0x66, 0x00, 0x14, 	/*Color of index 72*/
  0xc2, 0x61, 0x00, 0x15, 	/*Color of index 73*/
  0xc5, 0x5d, 0x00, 0x16, 	/*Color of index 74*/
  0xc6, 0x5e, 0x00, 0x1b, 	/*Color of index 75*/
  0xb3, 0x55, 0x00, 0x1b, 	/*Color of index 76*/
  0xb4, 0x6d, 0x15, 0x24, 	/*Color of index 77*/
  0xd2, 0x71, 0x00, 0x28, 	/*Color of index 78*/
  0xcc, 0x6c, 0x00, 0x28, 	/*Color of index 79*/
  0xc6, 0x66, 0x00, 0x28, 	/*Color of index 80*/
  0xb7, 0x5c, 0x00, 0x27, 	/*Color of index 81*/
  0xc7, 0x70, 0x0a, 0x32, 	/*Color of index 82*/
  0xb9, 0x6e, 0x14, 0x33, 	/*Color of index 83*/
  0xb7, 0x6f, 0x18, 0x35, 	/*Color of index 84*/
  0xc5, 0x65, 0x00, 0x35, 	/*Color of index 85*/
  0xd4, 0x70, 0x00, 0x3b, 	/*Color of index 86*/
  0xb2, 0x52, 0x00, 0x35, 	/*Color of index 87*/
  0xc5, 0x62, 0x00, 0x39, 	/*Color of index 88*/
  0xbf, 0x5b, 0x00, 0x38, 	/*Color of index 89*/
  0xd5, 0x70, 0x00, 0x42, 	/*Color of index 90*/
  0xd1, 0x6c, 0x00, 0x42, 	/*Color of index 91*/
  0xcd, 0x68, 0x00, 0x42, 	/*Color of index 92*/
  0xc2, 0x73, 0x0c, 0x54, 	/*Color of index 93*/
  0xc3, 0x63, 0x00, 0x55, 	/*Color of index 94*/
  0xbd, 0x5d, 0x00, 0x55, 	/*Color of index 95*/
  0xc0, 0x74, 0x12, 0x61, 	/*Color of index 96*/
  0xbf, 0x75, 0x17, 0x64, 	/*Color of index 97*/
  0xc5, 0x65, 0x00, 0x77, 	/*Color of index 98*/
  0xd4, 0x71, 0x00, 0x81, 	/*Color of index 99*/
  0xcf, 0x6e, 0x00, 0x80, 	/*Color of index 100*/
  0xcb, 0x68, 0x00, 0x7f, 	/*Color of index 101*/
  0xb2, 0x54, 0x00, 0x77, 	/*Color of index 102*/
  0xbf, 0x78, 0x15, 0x90, 	/*Color of index 103*/
  0xbe, 0x7a, 0x18, 0x92, 	/*Color of index 104*/
  0xc6, 0x65, 0x00, 0x86, 	/*Color of index 105*/
  0xc4, 0x75, 0x0d, 0x98, 	/*Color of index 106*/
  0xb7, 0x58, 0x00, 0x86, 	/*Color of index 107*/
  0xc2, 0x60, 0x00, 0x93, 	/*Color of index 108*/
  0xbb, 0x5a, 0x00, 0x93, 	/*Color of index 109*/
  0xc5, 0x84, 0x1b, 0xba, 	/*Color of index 110*/
  0xca, 0x82, 0x16, 0xb8, 	/*Color of index 111*/
  0xe9, 0xaf, 0x28, 0xff, 	/*Color of index 112*/
  0xe4, 0xac, 0x2a, 0xfe, 	/*Color of index 113*/
  0xe8, 0xac, 0x25, 0xff, 	/*Color of index 114*/
  0xc7, 0x87, 0x1c, 0xc7, 	/*Color of index 115*/
  0xd2, 0x6f, 0x00, 0xad, 	/*Color of index 116*/
  0xe6, 0xa9, 0x24, 0xff, 	/*Color of index 117*/
  0xca, 0x83, 0x18, 0xc7, 	/*Color of index 118*/
  0xc5, 0x64, 0x00, 0xab, 	/*Color of index 119*/
  0xe2, 0xa4, 0x22, 0xfe, 	/*Color of index 120*/
  0xdd, 0xa1, 0x25, 0xfa, 	/*Color of index 121*/
  0xcc, 0x88, 0x1c, 0xd5, 	/*Color of index 122*/
  0xd2, 0x92, 0x21, 0xe5, 	/*Color of index 123*/
  0xca, 0x85, 0x19, 0xd4, 	/*Color of index 124*/
  0xd1, 0x6f, 0x00, 0xbe, 	/*Color of index 125*/
  0xdd, 0x9c, 0x1e, 0xfc, 	/*Color of index 126*/
  0xc0, 0x62, 0x00, 0xb3, 	/*Color of index 127*/
  0xd2, 0x8b, 0x17, 0xe2, 	/*Color of index 128*/
  0xb7, 0x56, 0x00, 0xab, 	/*Color of index 129*/
  0xd1, 0x8e, 0x1d, 0xea, 	/*Color of index 130*/
  0xcf, 0x8d, 0x1b, 0xe8, 	/*Color of index 131*/
  0xc0, 0x5f, 0x00, 0xb3, 	/*Color of index 132*/
  0xae, 0x52, 0x00, 0xab, 	/*Color of index 133*/
  0xd1, 0x6e, 0x00, 0xc3, 	/*Color of index 134*/
  0xd8, 0x94, 0x1d, 0xff, 	/*Color of index 135*/
  0xd7, 0x92, 0x1b, 0xff, 	/*Color of index 136*/
  0xc5, 0x63, 0x00, 0xc3, 	/*Color of index 137*/
  0xd2, 0x70, 0x00, 0xd0, 	/*Color of index 138*/
  0xd0, 0x6c, 0x00, 0xcf, 	/*Color of index 139*/
  0xc8, 0x76, 0x10, 0xdd, 	/*Color of index 140*/
  0xbe, 0x5d, 0x00, 0xc2, 	/*Color of index 141*/
  0xc7, 0x66, 0x00, 0xce, 	/*Color of index 142*/
  0xd2, 0x8a, 0x18, 0xff, 	/*Color of index 143*/
  0xc8, 0x7a, 0x10, 0xe8, 	/*Color of index 144*/
  0xc7, 0x64, 0x00, 0xd2, 	/*Color of index 145*/
  0xd1, 0x6e, 0x00, 0xdd, 	/*Color of index 146*/
  0xcc, 0x81, 0x14, 0xfe, 	/*Color of index 147*/
  0xc9, 0x7d, 0x13, 0xff, 	/*Color of index 148*/
  0xc7, 0x66, 0x00, 0xe1, 	/*Color of index 149*/
  0xbf, 0x60, 0x00, 0xde, 	/*Color of index 150*/
  0xc6, 0x79, 0x11, 0xff, 	/*Color of index 151*/
  0xae, 0x51, 0x00, 0xd1, 	/*Color of index 152*/
  0xb9, 0x5a, 0x00, 0xdf, 	/*Color of index 153*/
  0xc5, 0x64, 0x00, 0xeb, 	/*Color of index 154*/
  0xc2, 0x72, 0x0f, 0xff, 	/*Color of index 155*/
  0xbb, 0x67, 0x09, 0xf2, 	/*Color of index 156*/
  0xb9, 0x59, 0x00, 0xe2, 	/*Color of index 157*/
  0xbe, 0x5e, 0x00, 0xea, 	/*Color of index 158*/
  0xd1, 0x6e, 0x00, 0xfe, 	/*Color of index 159*/
  0xbf, 0x6a, 0x0a, 0xff, 	/*Color of index 160*/
  0xcc, 0x6a, 0x00, 0xff, 	/*Color of index 161*/
  0xc8, 0x66, 0x00, 0xff, 	/*Color of index 162*/
  0xc3, 0x62, 0x00, 0xfd, 	/*Color of index 163*/
  0xaf, 0x50, 0x00, 0xed, 	/*Color of index 164*/
  0xbf, 0x5f, 0x00, 0xfe, 	/*Color of index 165*/
  0xba, 0x5a, 0x00, 0xfe, 	/*Color of index 166*/
  0xb6, 0x58, 0x01, 0xff, 	/*Color of index 167*/
  0xb2, 0x55, 0x00, 0xfe, 	/*Color of index 168*/
  0xad, 0x4f, 0x00, 0xf9, 	/*Color of index 169*/
  0xae, 0x51, 0x00, 0xff, 	/*Color of index 170*/
  0x00, 0x00, 0x00, 0x00, 	/*Color of index 171*/
  0x00, 0x00, 0x00, 0x00, 	/*Color of index 172*/
  0x00, 0x00, 0x00, 0x00, 	/*Color of index 173*/
  0x00, 0x00, 0x00, 0x00, 	/*Color of index 174*/
  0x00, 0x00, 0x00, 0x00, 	/*Color of index 175*/
  0x00, 0x00, 0x00, 0x00, 	/*Color of index 176*/
  0x00, 0x00, 0x00, 0x00, 	/*Color of index 177*/
  0x00, 0x00, 0x00, 0x00, 	/*Color of index 178*/
  0x00, 0x00, 0x00, 0x00, 	/*Color of index 179*/
  0x00, 0x00, 0x00, 0x00, 	/*Color of index 180*/
  0x00, 0x00, 0x00, 0x00, 	/*Color of index 181*/
  0x00, 0x00, 0x00, 0x00, 	/*Color of index 182*/
  0x00, 0x00, 0x00, 0x00, 	/*Color of index 183*/
  0x00, 0x00, 0x00, 0x00, 	/*Color of index 184*/
  0x00, 0x00, 0x00, 0x00, 	/*Color of index 185*/
  0x00, 0x00, 0x00, 0x00, 	/*Color of index 186*/
  0x00, 0x00, 0x00, 0x00, 	/*Color of index 187*/
  0x00, 0x00, 0x00, 0x00, 	/*Color of index 188*/
  0x00, 0x00, 0x00, 0x00, 	/*Color of index 189*/
  0x00, 0x00, 0x00, 0x00, 	/*Color of index 190*/
  0x00, 0x00, 0x00, 0x00, 	/*Color of index 191*/
  0x00, 0x00, 0x00, 0x00, 	/*Color of index 192*/
  0x00, 0x00, 0x00, 0x00, 	/*Color of index 193*/
  0x00, 0x00, 0x00, 0x00, 	/*Color of index 194*/
  0x00, 0x00, 0x00, 0x00, 	/*Color of index 195*/
  0x00, 0x00, 0x00, 0x00, 	/*Color of index 196*/
  0x00, 0x00, 0x00, 0x00, 	/*Color of index 197*/
  0x00, 0x00, 0x00, 0x00, 	/*Color of index 198*/
  0x00, 0x00, 0x00, 0x00, 	/*Color of index 199*/
  0x00, 0x00, 0x00, 0x00, 	/*Color of index 200*/
  0x00, 0x00, 0x00, 0x00, 	/*Color of index 201*/
  0x00, 0x00, 0x00, 0x00, 	/*Color of index 202*/
  0x00, 0x00, 0x00, 0x00, 	/*Color of index 203*/
  0x00, 0x00, 0x00, 0x00, 	/*Color of index 204*/
  0x00, 0x00, 0x00, 0x00, 	/*Color of index 205*/
  0x00, 0x00, 0x00, 0x00, 	/*Color of index 206*/
  0x00, 0x00, 0x00, 0x00, 	/*Color of index 207*/
  0x00, 0x00, 0x00, 0x00, 	/*Color of index 208*/
  0x00, 0x00, 0x00, 0x00, 	/*Color of index 209*/
  0x00, 0x00, 0x00, 0x00, 	/*Color of index 210*/
  0x00, 0x00, 0x00, 0x00, 	/*Color of index 211*/
  0x00, 0x00, 0x00, 0x00, 	/*Color of index 212*/
  0x00, 0x00, 0x00, 0x00, 	/*Color of index 213*/
  0x00, 0x00, 0x00, 0x00, 	/*Color of index 214*/
  0x00, 0x00, 0x00, 0x00, 	/*Color of index 215*/
  0x00, 0x00, 0x00, 0x00, 	/*Color of index 216*/
  0x00, 0x00, 0x00, 0x00, 	/*Color of index 217*/
  0x00, 0x00, 0x00, 0x00, 	/*Color of index 218*/
  0x00, 0x00, 0x00, 0x00, 	/*Color of index 219*/
  0x00, 0x00, 0x00, 0x00, 	/*Color of index 220*/
  0x00, 0x00, 0x00, 0x00, 	/*Color of index 221*/
  0x00, 0x00, 0x00, 0x00, 	/*Color of index 222*/
  0x00, 0x00, 0x00, 0x00, 	/*Color of index 223*/
  0x00, 0x00, 0x00, 0x00, 	/*Color of index 224*/
  0x00, 0x00, 0x00, 0x00, 	/*Color of index 225*/
  0x00, 0x00, 0x00, 0x00, 	/*Color of index 226*/
  0x00, 0x00, 0x00, 0x00, 	/*Color of index 227*/
  0x00, 0x00, 0x00, 0x00, 	/*Color of index 228*/
  0x00, 0x00, 0x00, 0x00, 	/*Color of index 229*/
  0x00, 0x00, 0x00, 0x00, 	/*Color of index 230*/
  0x00, 0x00, 0x00, 0x00, 	/*Color of index 231*/
  0x00, 0x00, 0x00, 0x00, 	/*Color of index 232*/
  0x00, 0x00, 0x00, 0x00, 	/*Color of index 233*/
  0x00, 0x00, 0x00, 0x00, 	/*Color of index 234*/
  0x00, 0x00, 0x00, 0x00, 	/*Color of index 235*/
  0x00, 0x00, 0x00, 0x00, 	/*Color of index 236*/
  0x00, 0x00, 0x00, 0x00, 	/*Color of index 237*/
  0x00, 0x00, 0x00, 0x00, 	/*Color of index 238*/
  0x00, 0x00, 0x00, 0x00, 	/*Color of index 239*/
  0x00, 0x00, 0x00, 0x00, 	/*Color of index 240*/
  0x00, 0x00, 0x00, 0x00, 	/*Color of index 241*/
  0x00, 0x00, 0x00, 0x00, 	/*Color of index 242*/
  0x00, 0x00, 0x00, 0x00, 	/*Color of index 243*/
  0x00, 0x00, 0x00, 0x00, 	/*Color of index 244*/
  0x00, 0x00, 0x00, 0x00, 	/*Color of index 245*/
  0x00, 0x00, 0x00, 0x00, 	/*Color of index 246*/
  0x00, 0x00, 0x00, 0x00, 	/*Color of index 247*/
  0x00, 0x00, 0x00, 0x00, 	/*Color of index 248*/
  0x00, 0x00, 0x00, 0x00, 	/*Color of index 249*/
  0x00, 0x00, 0x00, 0x00, 	/*Color of index 250*/
  0x00, 0x00, 0x00, 0x00, 	/*Color of index 251*/
  0x00, 0x00, 0x00, 0x00, 	/*Color of index 252*/
  0x00, 0x00, 0x00, 0x00, 	/*Color of index 253*/
  0x00, 0x00, 0x00, 0x00, 	/*Color of index 254*/
  0x00, 0x00, 0x00, 0x00, 	/*Color of index 255*/

  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x33, 0x1c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x37, 0x11, 0x1b, 0x21, 0x2a, 0x31, 0x33, 0x33, 0x31, 0x2a, 0x21, 0x1d, 0x0f, 0x00, 0x00, 0x00, 0x24, 0x34, 0x2c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0b, 0x1f, 0x2e, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x30, 0x1e, 0x14, 0x35, 0x35, 0x35, 0x0e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x20, 0x33, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x35, 0x34, 0x35, 0x32, 0x35, 0x34, 0x35, 0x1d, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x15, 0x31, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x35, 0x34, 0x35, 0x34, 0x35, 0x35, 0x35, 0x35, 0x35, 0x35, 0x2b, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x20, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x35, 0x34, 0x35, 0x35, 0x35, 0x35, 0x32, 0x35, 0x35, 0x35, 0x35, 0x35, 0x0d, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x23, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x35, 0x34, 0x35, 0x34, 0x35, 0x35, 0x35, 0x35, 0x35, 0x35, 0x35, 0x35, 0x35, 0x36, 0x35, 0x1c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x23, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x35, 0x28, 0x1e, 0x12, 0x0e, 0x05, 0x39, 0x08, 0x12, 0x1d, 0x29, 0x35, 0x32, 0x35, 0x36, 0x35, 0x36, 0x35, 0x36, 0x29, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x35, 0x21, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x17, 0x35, 0x36, 0x35, 0x36, 0x35, 0x36, 0x36, 0x32, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x15, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x2d, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x29, 0x36, 0x35, 0x36, 0x35, 0x36, 0x36, 0x29, 0x16, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x31, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x27, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x13, 0x35, 0x36, 0x35, 0x36, 0x29, 0x19, 0x43, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x25, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x16, 0x36, 0x26, 0x18, 0x09, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x0a, 0x33, 0x34, 0x34, 0x34, 0x34, 0x35, 0x2f, 0x41, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x34, 0x34, 0x34, 0x35, 0x34, 0x35, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x38, 0x2e, 0x34, 0x35, 0x34, 0x35, 0x34, 0x22, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x11, 0x34, 0x35, 0x34, 0x35, 0x35, 0x35, 0x0d, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x1e, 0x35, 0x34, 0x35, 0x35, 0x34, 0x2b, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x24, 0x34, 0x35, 0x35, 0x35, 0x35, 0x1e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x2c, 0x35, 0x35, 0x35, 0x35, 0x35, 0x13, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x32, 0x35, 0x35, 0x35, 0x36, 0x35, 0x0d, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x33, 0x36, 0x35, 0x36, 0x35, 0x36, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x86, 0x9f, 0x9f, 0xa1, 0xa1, 0x89, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x36, 0x35, 0x35, 0x35, 0x36, 0x35, 0x44, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x42, 0x9f, 0x9f, 0x9f, 0xa1, 0xa1, 0xa3, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x71, 0x36, 0x36, 0x36, 0x36, 0x36, 0x52, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x4e, 0x9f, 0x9f, 0x9f, 0xa1, 0xa1, 0x9a, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x79, 0x36, 0x35, 0x36, 0x36, 0x36, 0x5d, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x5a, 0x9f, 0x9f, 0x9f, 0xa1, 0xa1, 0x91, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x7b, 0x36, 0x36, 0x36, 0x36, 0x36, 0x6a, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x63, 0x9f, 0x9f, 0x9f, 0xa1, 0xa1, 0x77, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x6e, 0x36, 0x36, 0x36, 0x36, 0x36, 0x8c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x8a, 0x9f, 0x9f, 0x9f, 0xa1, 0xa1, 0x62, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x61, 0x36, 0x36, 0x36, 0x36, 0x70, 0x93, 0x51, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x4e, 0x9f, 0x9f, 0x9f, 0xa1, 0xa1, 0xa2, 0x55, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x3a, 0x78, 0x70, 0x36, 0x70, 0x36, 0x87, 0x81, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x74, 0x9f, 0x9f, 0x9f, 0xa1, 0xa1, 0x95, 0x38, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x73, 0x36, 0x70, 0x36, 0x70, 0x75, 0xa7, 0x59, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x56, 0x9f, 0x9f, 0x9f, 0xa1, 0xa1, 0xa1, 0x69, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x54, 0x72, 0x36, 0x70, 0x70, 0x70, 0xa0, 0x99, 0x49, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x45, 0x92, 0x9f, 0x9f, 0x9f, 0xa1, 0xa1, 0xa3, 0x4b, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7a, 0x70, 0x70, 0x70, 0x70, 0x8f, 0xa8, 0x8d, 0x3c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3b, 0x86, 0x9f, 0x9f, 0x9f, 0xa1, 0xa1, 0xa2, 0x6c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x4d, 0x75, 0x70, 0x70, 0x70, 0x75, 0xa7, 0xa7, 0x8d, 0x4a, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x45, 0x7d, 0x9f, 0x9f, 0x9f, 0xa1, 0xa1, 0xa1, 0x9a, 0x48, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x68, 0x70, 0x70, 0x70, 0x70, 0x94, 0xa8, 0xa6, 0x96, 0x58, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x56, 0x92, 0x9f, 0x9f, 0x9f, 0xa1, 0xa1, 0xa1, 0xa2, 0x5e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7a, 0x70, 0x72, 0x72, 0x75, 0xa6, 0xa8, 0xa5, 0xa5, 0x77, 0x50, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x4e, 0x74, 0x9f, 0x9f, 0x9f, 0xa1, 0xa1, 0xa1, 0xa2, 0xa2, 0x6c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3d, 0x83, 0x72, 0x70, 0x72, 0x88, 0xaa, 0xa7, 0xa6, 0xa5, 0xa3, 0x8e, 0x65, 0x5c, 0x4f, 0x40, 0x40, 0x4f, 0x5b, 0x64, 0x8b, 0x9f, 0x9f, 0xa1, 0x9f, 0xa1, 0xa1, 0xa1, 0xa2, 0xa2, 0x7f, 0x3a, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46, 0x82, 0x72, 0x72, 0x72, 0x94, 0xaa, 0xa7, 0xa5, 0xa5, 0xa5, 0xa2, 0xa2, 0xa1, 0xa1, 0xa1, 0xa1, 0xa1, 0xa1, 0xa1, 0xa1, 0xa1, 0xa1, 0xa1, 0xa1, 0xa2, 0xa2, 0xa3, 0x84, 0x3f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3e, 0x7c, 0x72, 0x75, 0x75, 0x9b, 0xaa, 0xa8, 0xa6, 0xa5, 0xa5, 0xa3, 0xa3, 0xa2, 0xa2, 0xa1, 0xa1, 0xa1, 0xa1, 0xa1, 0xa1, 0xa2, 0xa2, 0xa2, 0xa3, 0xa3, 0x6c, 0x3a, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x67, 0x78, 0x75, 0x75, 0x97, 0xaa, 0xa8, 0xa7, 0xa6, 0xa5, 0xa5, 0xa3, 0xa3, 0xa2, 0xa3, 0xa2, 0xa2, 0xa2, 0xa3, 0xa2, 0xa3, 0xa5, 0x9e, 0x5f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x4d, 0x7c, 0x75, 0x75, 0x8f, 0xa7, 0xaa, 0xa8, 0xa7, 0xa6, 0xa5, 0xa5, 0xa5, 0xa5, 0xa5, 0xa5, 0xa5, 0xa5, 0xa5, 0xa5, 0x6d, 0x47, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x53, 0x76, 0x7e, 0x78, 0x94, 0xaa, 0xaa, 0xa8, 0xa8, 0xa7, 0xa7, 0xa6, 0xa6, 0xa6, 0xa6, 0x9d, 0x6b, 0x4c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3a, 0x60, 0x6f, 0x80, 0x90, 0x9c, 0xa8, 0xa9, 0xa4, 0x98, 0x85, 0x66, 0x57, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
};

const lv_img_dsc_t ic_reset = {
  .header.cf = LV_COLOR_FORMAT_I8,
  //.header.always_zero = 0,
  //.header.reserved = 0,
  .header.w = 48,
  .header.h = 48,
  .data_size = 3328,
  .data = ic_reset_map,
};
