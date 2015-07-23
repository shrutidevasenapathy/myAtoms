#include <string.h>
#include <project.h>

#define DOUBLE_CONV_PRECISION `$Precision`
//we dont want to have power operator in code
#define TEN_TO_DOUBLE_CONV_PRECISION_POWER `$PowerOfPrecision`

//CONVERSION FUNCTIONS
int conv_i2str(char *str, int len, int val) {
  int ret = 0;
  int isNeg = (val < 0);
  if(isNeg) {*str++ = '-';  ret++; val *= -1;}
  char * tmp = str;
  while(val > 9 && ret < len) {
    *tmp++ = '0' + val%10;
    ret++;
    val /= 10;
  }
  *tmp++ = '0' + val%10;
  ret++;

  while(tmp-str > 1) {
    char t = *--tmp;
    *tmp = *str;
    *str++ = t;
  }

  return ret;//snprintf(str, len, "%d", val);
}
int conv_s2str(char *str, int len, char *val) {
  int vallen = 0;
  while(*val++ != '\0') vallen++;
  val -= vallen+1;

  if(len < vallen + 2) return 0;

  *str++ = '\"';
  memcpy(str, val, vallen);
  *(str+vallen) = '\"';

  return vallen + 2; //return snprintf(str, len, "\"%s\"", val);
}
int conv_d2str(char *str, int len, double val) {
  int t = (int) val;
  if(val < 0 && val > -1.0) t = -1;
  int ret = conv_i2str(str, len, t);
  if(val < 0 && val > -1.0) { str[1] = '0'; t = 0; } //dirty hack for -0.123 values
  char *tmp = str + ret;
  val -= t; //now it is only .123
  if(val < 0) val *= -1.0;
  if(val > (1.0/TEN_TO_DOUBLE_CONV_PRECISION_POWER)) {
    if(len - ret < 2) return ret; //we only have room for dot, so dont bother
    *tmp++ = '.';
    ret++;
    val *= 10.0;
    for(t = 0; t < DOUBLE_CONV_PRECISION && len - ret > 0; t++, val *= 10.0) {
      *tmp++ = '0' + (int)val;
      ret++;
      val -= (int)val;
    }
  }

  return ret;//snprintf(str, len, "%lf", val);
}
int conv_b2str(char *str, int len, unsigned char val) {
  if(val) {
    memcpy(str, "true", len < 4 ? len : 4);
    return len < 4 ? len : 4;
  } else {
    memcpy(str, "false", len < 5 ? len : 5);
    return len < 5 ? len : 5;
  }
}

int conv_str2i(const char *str, int len) {
  int x = 0;
  const char *tmp = str;
  //investigate 1 sign to check negative
  if(*str == '-') tmp++;
  while(tmp-str < len) {
    x = 10*x + (*tmp-'0');
    tmp++;
  }
  if(*str == '-') x *= -1;
  return x;
}

#define STRING_HOLDER_LEN 20
static char stringHolderForConversion[STRING_HOLDER_LEN];
char * conv_str2s(const char *str, int len) {
  memcpy(stringHolderForConversion, str, len > STRING_HOLDER_LEN ? STRING_HOLDER_LEN : len);
  return stringHolderForConversion;
}
double conv_str2d(const char *str, int len) {
  double x = 0.0;
  const char *tmp = str;
  if(*str == '-') tmp++;

  while(tmp-str < len && *tmp != '.') {
    x = 10*x + (*tmp-'0');
    tmp++;
  }
  if(*tmp == '.') {
    //dot spot here
    double y = 0.0;
    tmp = str+len-1;
    while(*tmp != '.') {
      y = ((*tmp-'0')+y)/10.0;
      tmp--;
    }
    x += y;
  }
  if(*str == '-') x *= -1.0;
  return x;
}
unsigned int conv_str2b(const char *str, int len) {
  return (str[0] == 't');
}


//CONVERSION HOLDERS FOR NON STANDARD IMPLEMENTATIONS
#define X(type, jsname) \
int conv_##jsname##2str(char *str, int len, type val) {return 0;} \
type conv_str2##jsname(const char *str, int len) {return 0;}
NON_PRIMITIVE_CONVS
#undef X


//TEST SUITE
// #include <stdio.h>
// int main(int argc, char const *argv[]) {
//   char buff[200];
//
//   printf("Conv i2str: %d\n", conv_i2str(buff, 200, 1234));
//   printf("I: %s\n", buff);
//   memset(buff, '\0', 200);
//   printf("Conv i2str: %d\n", conv_i2str(buff, 200, -1234));
//   printf("I: %s\n", buff);
//   memset(buff, '\0', 200);
//   printf("Conv i2str: %d\n", conv_i2str(buff, 200, -123456789));
//   printf("I: %s\n", buff);
//   memset(buff, '\0', 200);
//
//   printf("Conv d2str: %d\n", conv_d2str(buff, 200, -123.123));
//   printf("D: %s\n", buff);
//   memset(buff, '\0', 200);
//   printf("Conv d2str: %d\n", conv_d2str(buff, 200,  123.123));
//   printf("D: %s\n", buff);
//   memset(buff, '\0', 200);
//   printf("Conv d2str: %d\n", conv_d2str(buff, 200, -123));
//   printf("D: %s\n", buff);
//   memset(buff, '\0', 200);
//   printf("Conv d2str: %d\n", conv_d2str(buff, 200, 123));
//   printf("D: %s\n", buff);
//   memset(buff, '\0', 200);
//   printf("Conv d2str: %d\n", conv_d2str(buff, 200, -0.123));
//   printf("D: %s\n", buff);
//   memset(buff, '\0', 200);
//   printf("Conv d2str: %d\n", conv_d2str(buff, 200, 0.123));
//   printf("D: %s\n", buff);
//   memset(buff, '\0', 200);
//   printf("Conv d2str: %d\n", conv_d2str(buff, 6, -123.123));
//   printf("D: %s\n", buff);
//   memset(buff, '\0', 200);
//   printf("Conv d2str: %d\n", conv_d2str(buff, 5, -123.123));
//   printf("D: %s\n", buff);
//   memset(buff, '\0', 200);
//   printf("Conv d2str: %d\n", conv_d2str(buff, 3, -123.123));
//   printf("D: %s\n", buff);
//   memset(buff, '\0', 200);
//
//   printf("Conv b2str: %d\n", conv_b2str(buff, 200, 1));
//   printf("B: %s\n", buff);
//
//   printf("Conv s2str: %d\n", conv_s2str(buff, 200, "heheszki loool"));
//   printf("S: %s\n", buff);
//
//   return 0;
// }
