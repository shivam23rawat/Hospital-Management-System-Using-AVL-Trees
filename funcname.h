#define COUNT 10

// An AVL tree node with patient details
struct Patient
{
    char name[60];
    int age;
    int patientID;
    char gender;
    char disease[60];
    char treatment[60];
    char phone[11];
    char dob[11];
    char admit_date[11];
    int height;
    struct Patient *left;
    struct Patient *right;
};
typedef struct Patient patient;

int height(patient *N) ;
int maxint(int a, int b);
patient *rightRotate(patient *y);
patient *leftRotate(patient *x);
int getBalance(patient *N) ;
patient* newNode(int patientID) ;
patient* insert(patient* node,int key);
void displayAll(patient *root);
patient* search(patient* root,int key) ;
void displayNode(patient* root);
patient* minValueNode(patient* node); 
patient* del(patient *tTree, int delItem);
void clr();
void deletefile(int key);
patient* newNodeFromFile(char name[60],int age,int patientID,char gender,char disease[60],char treatment[60],char phone[11],char dob[11],char admit_date[11]);
patient* insertFromFile(patient* node,char name[60],int age,int patientID,char gender,char disease[60],char treatment[60],char phone[11],char dob[11],char admit_date[11]);
patient* load(patient *node); 
void print2DUtil(patient *root,int space);