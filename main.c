#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#include<windows.h>
#include "funcname.h"


int main() 
{ 
  patient *root = NULL; 
  root = load(root);
  int ch,patientID,key,dkey;
  patient *temp=NULL;
  system("cls");
  while(1)
  {
      printf("\nEnter 1 to Display list of all the patients:\t");
      printf("\nEnter 2 to Add a patient record to database:\t");
      printf("\nEnter 3 to Find patient:\t");
      printf("\nEnter 4 to Delete a patient record from database:\t");
      printf("\nEnter 5 to Print the tree:\t");
      printf("\nEnter 6 to Exit:\t");
      printf("\n Enter your Choice : ");
      scanf("%d",&ch);
      switch(ch)
      {
        case 1:
        system("cls");
        if(root==NULL)
                printf("\nDatabase Empty!");
            displayAll(root);
            clr();
            break;
        case 2:
            while(1)
            {
                system("cls");
                int flag=0;
                printf("\nEnter PatientID : ");
                scanf("%d",&patientID);
                temp=search(root,patientID);
                if(temp==NULL)
                {
                    root=insert(root,patientID);
                    printf("\nPatient added\n");
                    printf("\nPress Enter to continue\n");
	                getchar();
	                system("cls");
                    break;
                }
                else{
                    printf("\nID already exists!");
                    while(flag==0){
                        printf("\nPress Y to correct or N to exit to main menu\n");
                        char f;
                        f=getch();
                        if(f=='N'){
                            system("cls");
                            flag=1;
                            break;
                        }
                        else if(f=='Y'){
                            break;
                        }
                        else{
                            printf("Wrong Input! Press enter to try again.");
                        }
                    }
                }
                if(flag==1)break;
            }
            break;

        case 3:
            system("cls");
            printf("\nEnter ID of patient to be searched:\t");
            scanf("%d",&key);
            temp=search(root,key);
            displayNode(temp);
            clr();
            break;
        case 4:
            system("cls");
            printf("\nEnter ID of patient to be removed from database:\t");
            scanf("%d",&dkey);
            temp=search(root,dkey);
            if(temp==NULL)
                printf("\nRecord doesnt exist!");
            else
            {
                root=del(root,dkey);
                printf("\nPatient with ID %d removed\n",dkey);
                deletefile(dkey);
            }
            clr();
            break;
        case 5:
            system("cls");
            printf("\n");
            print2DUtil(root,0);
            clr();
            break;
        case 6:
            exit(0);
        default:
            printf("\nPlease Enter valid Input!!!");
            clr();
     }               
  }
    return 0; 
} 


