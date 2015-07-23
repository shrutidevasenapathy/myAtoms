#if !defined(CY_conv_comm_conv_H)
#define CY_conv_comm_conv_H
//CONVERSION FUNCTIONS
int conv_i2str(char *str, int len, int val);
int conv_s2str(char *str, int len, char *val);
int conv_d2str(char *str, int len, double val);
int conv_b2str(char *str, int len, unsigned char val);

int conv_str2i(const char *str, int len);
char * conv_str2s(const char *str, int len);
double conv_str2d(const char *str, int len);
unsigned int conv_str2b(const char *str, int len);


//CONVERSION HOLDERS FOR NON STANDARD IMPLEMENTATIONS
#define NON_PRIMITIVE_CONVS \
 X(int *, ia) \
 X(double *, da) \
 X(char **, sa) \
 X(char *, jo) \
 X(char *, oa)

#define X(type, jsname) \
int conv_##jsname##2str(char *str, int len, type val) __attribute__((weak)); \
type conv_str2##jsname(const char *str, int len) __attribute__((weak));
NON_PRIMITIVE_CONVS
#undef X

#endif /* CY_conv_comm_conv_H */
