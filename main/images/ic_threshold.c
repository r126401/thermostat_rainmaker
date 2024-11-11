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

#ifndef LV_ATTRIBUTE_IMG_IC_THRESHOLD
#define LV_ATTRIBUTE_IMG_IC_THRESHOLD
#endif

const LV_ATTRIBUTE_MEM_ALIGN LV_ATTRIBUTE_LARGE_CONST LV_ATTRIBUTE_IMG_IC_THRESHOLD uint8_t ic_threshold_map[] = {
  0x00, 0x00, 0x00, 0x00, 	/*Color of index 0*/
  0x80, 0x80, 0xff, 0x02, 	/*Color of index 1*/
  0x00, 0x00, 0xff, 0x01, 	/*Color of index 2*/
  0x55, 0x55, 0xaa, 0x03, 	/*Color of index 3*/
  0x33, 0x33, 0xcc, 0x05, 	/*Color of index 4*/
  0x55, 0x55, 0xd4, 0x06, 	/*Color of index 5*/
  0x49, 0x49, 0xb6, 0x07, 	/*Color of index 6*/
  0x40, 0x40, 0xbf, 0x08, 	/*Color of index 7*/
  0x39, 0x39, 0xc6, 0x09, 	/*Color of index 8*/
  0x46, 0x46, 0xd1, 0x0b, 	/*Color of index 9*/
  0x40, 0x40, 0xbf, 0x0e, 	/*Color of index 10*/
  0x44, 0x44, 0xcc, 0x0f, 	/*Color of index 11*/
  0x47, 0x47, 0xc6, 0x12, 	/*Color of index 12*/
  0x3c, 0x3c, 0xc3, 0x11, 	/*Color of index 13*/
  0x49, 0x49, 0xc2, 0x15, 	/*Color of index 14*/
  0x41, 0x41, 0xc9, 0x16, 	/*Color of index 15*/
  0x47, 0x47, 0xcc, 0x19, 	/*Color of index 16*/
  0x43, 0x43, 0xc6, 0x1b, 	/*Color of index 17*/
  0x43, 0x43, 0xc8, 0x21, 	/*Color of index 18*/
  0x41, 0x41, 0xc5, 0x23, 	/*Color of index 19*/
  0x45, 0x45, 0xc5, 0x2a, 	/*Color of index 20*/
  0x42, 0x42, 0xc7, 0x2c, 	/*Color of index 21*/
  0x44, 0x44, 0xc7, 0x32, 	/*Color of index 22*/
  0x41, 0x41, 0xc7, 0x34, 	/*Color of index 23*/
  0x42, 0x42, 0xc7, 0x38, 	/*Color of index 24*/
  0x43, 0x43, 0xc6, 0x3d, 	/*Color of index 25*/
  0x43, 0x43, 0xc8, 0x41, 	/*Color of index 26*/
  0x44, 0x44, 0xc6, 0x47, 	/*Color of index 27*/
  0x42, 0x42, 0xc6, 0x49, 	/*Color of index 28*/
  0x41, 0x41, 0xc8, 0x4a, 	/*Color of index 29*/
  0x44, 0x44, 0xc7, 0x52, 	/*Color of index 30*/
  0x43, 0x43, 0xc6, 0x55, 	/*Color of index 31*/
  0x42, 0x42, 0xc7, 0x59, 	/*Color of index 32*/
  0x44, 0x44, 0xc7, 0x5e, 	/*Color of index 33*/
  0x42, 0x42, 0xc7, 0x64, 	/*Color of index 34*/
  0x42, 0x42, 0xc7, 0x67, 	/*Color of index 35*/
  0x43, 0x43, 0xc7, 0x69, 	/*Color of index 36*/
  0x46, 0x46, 0xc8, 0x6d, 	/*Color of index 37*/
  0x43, 0x43, 0xc6, 0x73, 	/*Color of index 38*/
  0x43, 0x43, 0xc7, 0x7b, 	/*Color of index 39*/
  0x43, 0x43, 0xc7, 0x7d, 	/*Color of index 40*/
  0x43, 0x43, 0xc7, 0x80, 	/*Color of index 41*/
  0x43, 0x43, 0xc8, 0x86, 	/*Color of index 42*/
  0x42, 0x42, 0xc6, 0x8b, 	/*Color of index 43*/
  0x8d, 0x8d, 0xf6, 0xff, 	/*Color of index 44*/
  0x43, 0x43, 0xc7, 0x93, 	/*Color of index 45*/
  0x43, 0x43, 0xc8, 0x9d, 	/*Color of index 46*/
  0x44, 0x44, 0xc7, 0x9e, 	/*Color of index 47*/
  0x42, 0x42, 0xc6, 0xa2, 	/*Color of index 48*/
  0x44, 0x44, 0xc8, 0xa6, 	/*Color of index 49*/
  0x48, 0x48, 0xc9, 0xab, 	/*Color of index 50*/
  0x44, 0x44, 0xc8, 0xaa, 	/*Color of index 51*/
  0x42, 0x42, 0xc6, 0xa9, 	/*Color of index 52*/
  0x7c, 0x7c, 0xeb, 0xff, 	/*Color of index 53*/
  0x42, 0x42, 0xc6, 0xb1, 	/*Color of index 54*/
  0x48, 0x48, 0xcb, 0xb9, 	/*Color of index 55*/
  0x43, 0x43, 0xc7, 0xb8, 	/*Color of index 56*/
  0x42, 0x42, 0xc6, 0xbd, 	/*Color of index 57*/
  0x42, 0x42, 0xc7, 0xc2, 	/*Color of index 58*/
  0x43, 0x43, 0xc6, 0xc8, 	/*Color of index 59*/
  0x48, 0x48, 0xcb, 0xd0, 	/*Color of index 60*/
  0x45, 0x45, 0xc9, 0xce, 	/*Color of index 61*/
  0x5a, 0x5a, 0xd5, 0xed, 	/*Color of index 62*/
  0x60, 0x60, 0xd8, 0xf7, 	/*Color of index 63*/
  0x5c, 0x5c, 0xd6, 0xf2, 	/*Color of index 64*/
  0x42, 0x42, 0xc6, 0xd3, 	/*Color of index 65*/
  0x55, 0x55, 0xd3, 0xef, 	/*Color of index 66*/
  0x56, 0x56, 0xd2, 0xf1, 	/*Color of index 67*/
  0x42, 0x42, 0xc6, 0xd7, 	/*Color of index 68*/
  0x42, 0x42, 0xc6, 0xdd, 	/*Color of index 69*/
  0x48, 0x48, 0xca, 0xe7, 	/*Color of index 70*/
  0x42, 0x42, 0xc6, 0xe1, 	/*Color of index 71*/
  0x4b, 0x4b, 0xcc, 0xef, 	/*Color of index 72*/
  0x45, 0x45, 0xc8, 0xe8, 	/*Color of index 73*/
  0x47, 0x47, 0xc8, 0xf0, 	/*Color of index 74*/
  0x43, 0x43, 0xc7, 0xed, 	/*Color of index 75*/
  0x43, 0x43, 0xc7, 0xf4, 	/*Color of index 76*/
  0x00, 0x00, 0x00, 0x00, 	/*Color of index 77*/
  0x00, 0x00, 0x00, 0x00, 	/*Color of index 78*/
  0x00, 0x00, 0x00, 0x00, 	/*Color of index 79*/
  0x00, 0x00, 0x00, 0x00, 	/*Color of index 80*/
  0x00, 0x00, 0x00, 0x00, 	/*Color of index 81*/
  0x00, 0x00, 0x00, 0x00, 	/*Color of index 82*/
  0x00, 0x00, 0x00, 0x00, 	/*Color of index 83*/
  0x00, 0x00, 0x00, 0x00, 	/*Color of index 84*/
  0x00, 0x00, 0x00, 0x00, 	/*Color of index 85*/
  0x00, 0x00, 0x00, 0x00, 	/*Color of index 86*/
  0x00, 0x00, 0x00, 0x00, 	/*Color of index 87*/
  0x00, 0x00, 0x00, 0x00, 	/*Color of index 88*/
  0x00, 0x00, 0x00, 0x00, 	/*Color of index 89*/
  0x00, 0x00, 0x00, 0x00, 	/*Color of index 90*/
  0x00, 0x00, 0x00, 0x00, 	/*Color of index 91*/
  0x00, 0x00, 0x00, 0x00, 	/*Color of index 92*/
  0x00, 0x00, 0x00, 0x00, 	/*Color of index 93*/
  0x00, 0x00, 0x00, 0x00, 	/*Color of index 94*/
  0x00, 0x00, 0x00, 0x00, 	/*Color of index 95*/
  0x00, 0x00, 0x00, 0x00, 	/*Color of index 96*/
  0x00, 0x00, 0x00, 0x00, 	/*Color of index 97*/
  0x00, 0x00, 0x00, 0x00, 	/*Color of index 98*/
  0x00, 0x00, 0x00, 0x00, 	/*Color of index 99*/
  0x00, 0x00, 0x00, 0x00, 	/*Color of index 100*/
  0x00, 0x00, 0x00, 0x00, 	/*Color of index 101*/
  0x00, 0x00, 0x00, 0x00, 	/*Color of index 102*/
  0x00, 0x00, 0x00, 0x00, 	/*Color of index 103*/
  0x00, 0x00, 0x00, 0x00, 	/*Color of index 104*/
  0x00, 0x00, 0x00, 0x00, 	/*Color of index 105*/
  0x00, 0x00, 0x00, 0x00, 	/*Color of index 106*/
  0x00, 0x00, 0x00, 0x00, 	/*Color of index 107*/
  0x00, 0x00, 0x00, 0x00, 	/*Color of index 108*/
  0x00, 0x00, 0x00, 0x00, 	/*Color of index 109*/
  0x00, 0x00, 0x00, 0x00, 	/*Color of index 110*/
  0x00, 0x00, 0x00, 0x00, 	/*Color of index 111*/
  0x00, 0x00, 0x00, 0x00, 	/*Color of index 112*/
  0x00, 0x00, 0x00, 0x00, 	/*Color of index 113*/
  0x00, 0x00, 0x00, 0x00, 	/*Color of index 114*/
  0x00, 0x00, 0x00, 0x00, 	/*Color of index 115*/
  0x00, 0x00, 0x00, 0x00, 	/*Color of index 116*/
  0x00, 0x00, 0x00, 0x00, 	/*Color of index 117*/
  0x00, 0x00, 0x00, 0x00, 	/*Color of index 118*/
  0x00, 0x00, 0x00, 0x00, 	/*Color of index 119*/
  0x00, 0x00, 0x00, 0x00, 	/*Color of index 120*/
  0x00, 0x00, 0x00, 0x00, 	/*Color of index 121*/
  0x00, 0x00, 0x00, 0x00, 	/*Color of index 122*/
  0x00, 0x00, 0x00, 0x00, 	/*Color of index 123*/
  0x00, 0x00, 0x00, 0x00, 	/*Color of index 124*/
  0x00, 0x00, 0x00, 0x00, 	/*Color of index 125*/
  0x00, 0x00, 0x00, 0x00, 	/*Color of index 126*/
  0x00, 0x00, 0x00, 0x00, 	/*Color of index 127*/
  0x00, 0x00, 0x00, 0x00, 	/*Color of index 128*/
  0x00, 0x00, 0x00, 0x00, 	/*Color of index 129*/
  0x00, 0x00, 0x00, 0x00, 	/*Color of index 130*/
  0x00, 0x00, 0x00, 0x00, 	/*Color of index 131*/
  0x00, 0x00, 0x00, 0x00, 	/*Color of index 132*/
  0x00, 0x00, 0x00, 0x00, 	/*Color of index 133*/
  0x00, 0x00, 0x00, 0x00, 	/*Color of index 134*/
  0x00, 0x00, 0x00, 0x00, 	/*Color of index 135*/
  0x00, 0x00, 0x00, 0x00, 	/*Color of index 136*/
  0x00, 0x00, 0x00, 0x00, 	/*Color of index 137*/
  0x00, 0x00, 0x00, 0x00, 	/*Color of index 138*/
  0x00, 0x00, 0x00, 0x00, 	/*Color of index 139*/
  0x00, 0x00, 0x00, 0x00, 	/*Color of index 140*/
  0x00, 0x00, 0x00, 0x00, 	/*Color of index 141*/
  0x00, 0x00, 0x00, 0x00, 	/*Color of index 142*/
  0x00, 0x00, 0x00, 0x00, 	/*Color of index 143*/
  0x00, 0x00, 0x00, 0x00, 	/*Color of index 144*/
  0x00, 0x00, 0x00, 0x00, 	/*Color of index 145*/
  0x00, 0x00, 0x00, 0x00, 	/*Color of index 146*/
  0x00, 0x00, 0x00, 0x00, 	/*Color of index 147*/
  0x00, 0x00, 0x00, 0x00, 	/*Color of index 148*/
  0x00, 0x00, 0x00, 0x00, 	/*Color of index 149*/
  0x00, 0x00, 0x00, 0x00, 	/*Color of index 150*/
  0x00, 0x00, 0x00, 0x00, 	/*Color of index 151*/
  0x00, 0x00, 0x00, 0x00, 	/*Color of index 152*/
  0x00, 0x00, 0x00, 0x00, 	/*Color of index 153*/
  0x00, 0x00, 0x00, 0x00, 	/*Color of index 154*/
  0x00, 0x00, 0x00, 0x00, 	/*Color of index 155*/
  0x00, 0x00, 0x00, 0x00, 	/*Color of index 156*/
  0x00, 0x00, 0x00, 0x00, 	/*Color of index 157*/
  0x00, 0x00, 0x00, 0x00, 	/*Color of index 158*/
  0x00, 0x00, 0x00, 0x00, 	/*Color of index 159*/
  0x00, 0x00, 0x00, 0x00, 	/*Color of index 160*/
  0x00, 0x00, 0x00, 0x00, 	/*Color of index 161*/
  0x00, 0x00, 0x00, 0x00, 	/*Color of index 162*/
  0x00, 0x00, 0x00, 0x00, 	/*Color of index 163*/
  0x00, 0x00, 0x00, 0x00, 	/*Color of index 164*/
  0x00, 0x00, 0x00, 0x00, 	/*Color of index 165*/
  0x00, 0x00, 0x00, 0x00, 	/*Color of index 166*/
  0x00, 0x00, 0x00, 0x00, 	/*Color of index 167*/
  0x00, 0x00, 0x00, 0x00, 	/*Color of index 168*/
  0x00, 0x00, 0x00, 0x00, 	/*Color of index 169*/
  0x00, 0x00, 0x00, 0x00, 	/*Color of index 170*/
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

  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x12, 0x19, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x17, 0x15, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x14, 0x30, 0x4b, 0x49, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x19, 0x38, 0x4c, 0x39, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x16, 0x33, 0x41, 0x21, 0x39, 0x36, 0x21, 0x00, 0x00, 0x00, 0x00, 0x1c, 0x3a, 0x3a, 0x1c, 0x47, 0x41, 0x15, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x22, 0x1f, 0x01, 0x11, 0x45, 0x14, 0x41, 0x01, 0x00, 0x00, 0x00, 0x28, 0x19, 0x00, 0x1b, 0x36, 0x20, 0x31, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x2b, 0x26, 0x00, 0x33, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x39, 0x19, 0x03, 0x44, 0x13, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x0c, 0x45, 0x0a, 0x00, 0x17, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x19, 0x3a, 0x00, 0x00, 0x22, 0x26, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x29, 0x28, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x36, 0x1d, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x09, 0x45, 0x0d, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x16, 0x3d, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x26, 0x2b, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x34, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x11, 0x12, 0x12, 0x11, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x41, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0b, 0x45, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46, 0x48, 0x48, 0x49, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x0f, 0x41, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1d, 0x2f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x4a, 0x2c, 0x2c, 0x48, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x17, 0x36, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x23, 0x29, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x14, 0x21, 0x07, 0x18, 0x3c, 0x40, 0x2c, 0x2c, 0x40, 0x3c, 0x18, 0x07, 0x21, 0x14, 0x00, 0x00, 
  0x00, 0x12, 0x3b, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1e, 0x2d, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3c, 0x43, 0x4a, 0x48, 0x35, 0x2c, 0x2c, 0x2c, 0x2c, 0x35, 0x48, 0x4a, 0x43, 0x3c, 0x00, 0x00, 
  0x00, 0x02, 0x45, 0x0a, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x11, 0x41, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x43, 0x2c, 0x2c, 0x2c, 0x2c, 0x2c, 0x2c, 0x2c, 0x2c, 0x2c, 0x2c, 0x2c, 0x2c, 0x43, 0x1f, 0x00, 
  0x00, 0x00, 0x2d, 0x24, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3a, 0x18, 0x00, 0x00, 0x00, 0x00, 0x37, 0x3f, 0x2c, 0x2c, 0x2c, 0x2c, 0x42, 0x46, 0x46, 0x43, 0x2c, 0x2c, 0x2c, 0x2c, 0x3f, 0x37, 0x00, 
  0x00, 0x00, 0x12, 0x44, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1e, 0x33, 0x00, 0x00, 0x00, 0x00, 0x07, 0x32, 0x40, 0x2c, 0x2c, 0x42, 0x25, 0x00, 0x00, 0x25, 0x43, 0x2c, 0x2c, 0x40, 0x32, 0x07, 0x00, 
  0x00, 0x00, 0x00, 0x33, 0x1e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x44, 0x13, 0x00, 0x00, 0x00, 0x00, 0x1a, 0x3e, 0x2c, 0x2c, 0x46, 0x00, 0x00, 0x00, 0x00, 0x46, 0x2c, 0x2c, 0x3e, 0x1a, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x16, 0x3b, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x24, 0x2d, 0x00, 0x00, 0x00, 0x00, 0x1a, 0x3e, 0x2c, 0x2c, 0x46, 0x00, 0x00, 0x00, 0x00, 0x46, 0x2c, 0x2c, 0x3e, 0x1a, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x39, 0x19, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x45, 0x0f, 0x00, 0x00, 0x07, 0x32, 0x40, 0x2c, 0x2c, 0x43, 0x25, 0x00, 0x00, 0x25, 0x43, 0x2c, 0x2c, 0x40, 0x32, 0x07, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x1b, 0x36, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x27, 0x29, 0x00, 0x00, 0x37, 0x3f, 0x2c, 0x2c, 0x2c, 0x2c, 0x43, 0x46, 0x46, 0x42, 0x2c, 0x2c, 0x2c, 0x2c, 0x3f, 0x37, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x02, 0x45, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x44, 0x00, 0x00, 0x1f, 0x42, 0x2c, 0x2c, 0x2c, 0x2c, 0x2c, 0x2c, 0x2c, 0x2c, 0x2c, 0x2c, 0x2c, 0x2c, 0x43, 0x1f, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x2f, 0x1d, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x41, 0x0f, 0x00, 0x00, 0x3c, 0x43, 0x4a, 0x48, 0x35, 0x2c, 0x2c, 0x2c, 0x2c, 0x35, 0x48, 0x4a, 0x43, 0x3c, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x2a, 0x21, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x38, 0x14, 0x00, 0x00, 0x14, 0x21, 0x07, 0x18, 0x3c, 0x40, 0x2c, 0x2c, 0x40, 0x3c, 0x18, 0x07, 0x21, 0x14, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x34, 0x1a, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x45, 0x0a, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x48, 0x2c, 0x2c, 0x4a, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x05, 0x47, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x14, 0x3b, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x49, 0x48, 0x48, 0x46, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x21, 0x2e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x2d, 0x24, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x11, 0x12, 0x12, 0x11, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x02, 0x3d, 0x15, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x47, 0x09, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x1d, 0x36, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x27, 0x29, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x39, 0x19, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x45, 0x0e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x17, 0x3b, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x24, 0x2d, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x30, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x41, 0x13, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x04, 0x47, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x14, 0x3b, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x13, 0x3a, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x2b, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x09, 0x13, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0e, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
};

const lv_img_dsc_t ic_threshold = {
  .header.cf = LV_COLOR_FORMAT_I8,
  //.header.always_zero = 0,
  //.header.reserved = 0,
  .header.w = 36,
  .header.h = 36,
  .data_size = 2320,
  .data = ic_threshold_map,
};
