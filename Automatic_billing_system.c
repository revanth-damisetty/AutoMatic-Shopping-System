
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct costumer{
    //used to store user data.
    char name[30];
    int mobile;
    float purchase;
};

struct product{
    //used to store the data of each product in the store.
    char name[30];
    int qty;
    int price;
};

void report(struct costumer arr[],int person){
    int dd,mm,yyyy;
    FILE *s=fopen("report.txt","a");//File pointer is now opened in append mode.
    printf("please enter the date in DD MM YYYY format for the report:");
    scanf("%d %d %d",&dd,&mm,&yyyy);//Date is collected and printed in the report.
    fprintf(s,"\n\nDate: %d-%d-%d\n\n",dd,mm,yyyy);
   
    for (int i=0;i<person;i++){//purchase of each costumer is printed in the report.
        fprintf(s,"%d %s  %0.2f\n",arr[i].mobile,arr[i].name,arr[i].purchase);
    }
    printf("->Report of today's purchase list is added to the report");
    
}
    
void billmaker(int n,int goods[],struct product items[],struct costumer arr[],int t){
    int *p=goods;//pointer p is assigned for int array goods
    int sum=0,subtotal,q=1;// sum is the total bill Amount
    //subtotal is the bill amount for each item and q is the Sno
    //goods array is the virtual representation of the customer basket.
    printf("_______________________________________________________\n");
    printf("|Sno|       Name       | Quantity | Price |Amount|\n");
    printf("-------------------------------------------------------\n");
   
    for (int i=0;i<n;i++){
        if (*(p+i)>0 && items[i].price>0 && *(p+i)<1000){
            subtotal=(*(p+i))*items[i].price;
            sum+=subtotal;
            printf("| %-2d|     %-13s|    %-6d|",q++,items[i].name,*(p+i));
            printf("%-4d|%-4d|\n",items[i].price,subtotal);
        }
    }
    printf("_______________________________________________________\n");
    printf("Total Amount of purchase = RS%d\n",sum);
    //classification of costumers;
    float sp;
    if (sum > 5000){//availing 5% discount;
        sp=0.95*sum;
        printf("Discount availed on purchase(Under Platinum slab)= %f  \n",0.05*sum);
    }else if (sum>3000){//availing 3% discount;
        sp=0.97*sum;
        printf("Discount availed on purchase(Under Gold slab)= %f  \n",0.03*sum);
    }
    else if (sum>1500){//availing 2% discount;
        sp=0.98*sum;
        printf("Discount availed on purchase(Under Silver slab)= %f  \n",0.02*sum);
    }
    else{
        //the cost remains the same;
        sp=sum;
    }
    printf("Final Price= RS %0.2f\n",sp);
    arr[t].purchase = sp;
}


int main()
{
    
    void billmaker(int,int[],struct product [],struct costumer [],int);
    void report(struct costumer arr[],int);
    
    FILE *fp=fopen("start.txt","r");//File pointer is opened in read mode to
    int total,left,n;//retrieve data back from the file on stock availability.
    printf("Please enter the no of new products:");
    scanf("%d",&n);
    fscanf(fp,"%d %d",&total,&left);
    if ((total-left)<n){//if the size of total isn't sufficent to fill the new products;
        total+=(n-(total-left));//left is the existing products in the list;
    }//total is the maximum index used to represent a item in the list;
    //
    //
    struct product items[total];//items list is being declared
    int index;
    //
    for (int i=0;i<total;i++){//the contents of the structure are assigned zero
        items[i].price=0;//for less garbage values to encounter.
        items[i].qty=0;
    }
    
    for (int i=0;i<left;i++){//data from the start.txt is being retrieved.
        fscanf(fp,"%d",&index);
        fscanf(fp,"%s %d %d",items[index].name,&items[index].price,&items[index].qty);
    }
    
    for (int i=0;i<n;i++){
        int flag=1;
        char name[20];
        printf("Enter the name of the product:");
        scanf("%s",name);
        for (int j=0;j<total;j++){
            if (!(strcmp(name,items[j].name))){// when the product already exists in the list
                int d=items[j].qty,e;
                printf("Enter the no of items:");
                scanf("%d",&e);
                for (int c=d+1;c<d+e+1;c++){
                    printf("%d\n",(j+1)*10000+c);
                }
                items[j].qty+=e;//qty of the existing product is updated.
                flag=0;
                break;
            }
        }
        int t=0;
        if (flag){//when its a new product into the market.
            while (items[t].price>0 && items[t].qty>0){
            t++;//finding the first vacant index in the list;
            }
            strcpy(items[t].name,name);
            printf("Enter the price of the product:");
            scanf("%d",&items[t].price);
            printf("Enter the no of items:");
            int x;
            scanf("%d",&x);
            printf("the rfid codes are:\n");
            for (int c=1;c<=x;c++){
                printf("%d\n",(t+1)*10000+c);
            }
            items[t].qty+=x;
        }
        
    }
        
    fclose(fp);
    
 
    //By this the process of data retrieval and data updation is over.
    //Here the console starts to face the user for shopping for the entire day.


    struct costumer arr[1000];
    for (int i=0;i<1000;i++){//assigned zero for less garbage values.
        arr[i].mobile=0;
        arr[i].purchase=0;
    }
    int person=0;
    int goods[total],t;
    do{//loop is continued till the end of the day.Stopped by a secret code(1234)
        for (int i=0;i<total;i++){
            goods[i]=0;//re-initalizing the basket to an empty basket
        }
        puts("\nWELCOME TO THE SUPERMART\n");
        printf("Enter your name:");
        scanf("%s",arr[person].name);
        printf("Enter your mobile no:");
        scanf("%d",&arr[person].mobile);
        do{
            int no;
            printf("\nplease enter the rfid:");
            scanf("%d",&t);
            t=(t/10000)-1;
            do{//repeats while the no of items needed is invalid.
                printf("\n|Name: %s | Price: %d|\n",items[t].name,items[t].price);
                printf("\nthere are only %d pieces left!\n",items[t].qty);
                printf("-Enter a +ve value for adding\n");
                printf("-Enter a -ve value for removing\n\n");
                printf("please enter the no of items required:");
                scanf("%d",&no);
            }while(no>items[t].qty || goods[t]+no<0);
            //when the realistic condition is met the basket and list are updated.
            goods[t]+=no;
            items[t].qty-=no;
            printf("\n->press any key to continue shopping else 0:");
            scanf("%d",&t);
        }while(t!=0);
        billmaker(total,goods,items,arr,person++);
        //bill is printed at the end of the function billmaker().
        printf("\n->press any key to start shopping:");
        scanf("%d",&t);
    }while(t!=1234);
    
    //at the end of the day the daily report is appended.
    report(arr,person);
    
    FILE *fp1;//the inventory file is overwritten with the present stock available.
    fp1=fopen("start.txt","w");
    left=0;
    for (int i=0;i<total;i++){
        if (items[i].qty>0 && items[i].price>0){
            left++;
        }
    }
    fprintf(fp1,"%d %d\n",total,left);
    for (int i=0;i<total;i++){
        if (items[i].qty>0 && items[i].price>0){
            fprintf(fp1,"%d %s %d %d\n",i,items[i].name,items[i].price,items[i].qty);
        }
    }
    fclose(fp1);
}

