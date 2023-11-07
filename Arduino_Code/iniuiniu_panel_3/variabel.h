// Set the rosserial socket server IP address
IPAddress server(192,168,1,157);
// Set the rosserial socket server port
const uint16_t serverPort = 11411;

ros::NodeHandle nh;
std_msgs::String str_msg;
ros::Publisher topik("topik_hidayat", &str_msg);

char topik_incity1[15] = "outcity1=clear";
char topik_incity2[15] = "outcity2=clear";
char topik_incity3[15] = "outcity3=clear";

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
