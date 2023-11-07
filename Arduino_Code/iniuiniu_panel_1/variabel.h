// Set the rosserial socket server IP address
IPAddress server(192,168,1,157);
// Set the rosserial socket server port
const uint16_t serverPort = 11411;

ros::NodeHandle nh;
std_msgs::String str_msg;
ros::Publisher topik("topik_hidayat", &str_msg);

char topik_incity1[14] = "incity1=req";
char topik_incity2[14] = "incity2=req";
char topik_incity3[14] = "incity3=req";
char topik_outcity1[15] = "outcity1=req";
char topik_outcity2[15] = "outcity2=req";
char topik_outcity3[15] = "outcity3=req";
char topik_icebox_clear[21] = "incityemptybox=clear";
char topik_ocebox_clear[22] = "outcityemptybox=clear";
char topik_icebox_blocked[23] = "incityemptybox=blocked";
char topik_ocebox_blocked[24] = "outcityemptybox=blocked";

int sensor1 = 13;
int sensor2 = 35;
int sensor3 = 34;
int sensor4 = 39;
int sensor5 = 36;
int sensor6 = 4;
int sensor7 = 19;
int sensor8 = 21;
int sensor9 = 22;
int sensor10 = 23;

int out1 = 32;
int out2 = 33;
int out3 = 25;
int out4 = 26;
int out5 = 27;

bool buzzState = false;
bool buzz = false;
