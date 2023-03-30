#include<stdio.h>
#include<string.h>
#include<stdlib.h>
struct items
{
    char item[20];
    float price;
    int qty;
};
struct orders
{
    char customer[50];
    char date[50];
    int numOfItems;
    struct items itm[50];
    

};
void generateBillHeader(char name[50],char date[30]){
    printf("\n\n");
    printf("\t    Restaurant   ");
    printf("\n\t---------------------");
    printf("\nDate:%s",date);
    printf("\nInvoice To:%s",name);
   // printf("\n");
    printf("\n--------------------------------------------------------\n");
   
    printf("Items\t\t");
    printf("Quantity\t\t");
    printf("Total\t\t");
    printf("\n--------------------------------------------------------");
    printf("\n\n");
}
void generateBillBody(char item[30],int qty,float price){
    printf("%s\t\t",item);
    printf("%d\t\t",qty);
    printf("%.2f\t\t",qty*price);
    printf("\n");
}
void generateBillFooter(float total){
    printf("\n");
    float dis=0.1*total;
    float netTotal=total-dis;
    float cgst=0.09*netTotal,grandTotal=netTotal+2*cgst;
    printf("--------------------------------------------------------\n");
    printf("Sub Total \t\t\t%.2f",total);
    printf("\nDicount \t\t\t%.2f",dis);
    printf("\n\t\t\t\t------------------------");
    printf("\n Net  \t\t\t\t%.2f",netTotal);
    printf("\n CGST \t\t\t\t%.2f",cgst);
    printf("\n SGST \t\t\t\t%.2f",cgst);
    printf("\n--------------------------------------------------------\n");
    printf("\n Grand Total \t\t\t %.2f",grandTotal);
    printf("\n-------------------------------------------------------");


}
int main(){
    //dashboard
    int opr ,invoiceFound;
    float toatl;
    struct orders ordr;
    struct orders od;
    char saveBill='y',contFlag='y';
    char name[20];
    FILE *fp;
    while (contFlag=='y')
    {
        toatl=0;
        invoiceFound=0;
        system("clear");
    
    printf("\t=====================Restaurant Billing=====================");
    printf("\n\n Please select your prefered operation ");
    printf("\n1.Generate Invoice");
    printf("\n2.Show all Invoice");
    printf("\n3.Search Invoice");
    printf("\n4.Exit");
    printf("\n Your choice:\t");
    scanf("%d",&opr);
    printf("\n");
    int n;
    fgetc(stdin);
    switch (opr)
    {
    case 1:
        printf("Please enter the name of the customer \t");
        fgets(ordr.customer,50,stdin);
        ordr.customer[strlen(ordr.customer)-1]=0;
        strcpy(ordr.date,__DATE__);
        printf("Please enter the number of items \t");
        scanf("%d",&n);
        ordr.numOfItems=n;
        for (int i = 0; i < n; i++)
        {
            fgetc(stdin);
            printf("\n\n");
            printf("Please enter the item: %d \t",i+1);
            fgets(ordr.itm[i].item,20,stdin);
            ordr.itm[i].item[strlen(ordr.itm[i].item)-1]=0;
            printf("Please enter the quantity: \t");
            scanf("%d",&ordr.itm[i].qty);
            printf("Please enter the unit price: \t");
            scanf("%f",&ordr.itm[i].price);
            toatl+=ordr.itm[i].qty*ordr.itm[i].price;
        
        }
        generateBillHeader(ordr.customer,ordr.date);
        for (int i = 0; i < ordr.numOfItems; i++)
        {
            generateBillBody(ordr.itm[i].item,ordr.itm[i].qty,ordr.itm[i].price);
        }
        generateBillFooter(toatl);
        printf("\n Do you want to save the invoice [Y/N]: \t");
        scanf("%s",&saveBill);
        if (saveBill=='y')
        {
            fp=fopen("RestaurantBill.dat","a+");
            fwrite(&ordr,sizeof(struct orders),1,fp);
            if (fwrite !=0)
            {
                printf("\nSucssefully saved");

            }
            else
            {
                printf("\n Error saving");

            }
            fclose(fp);
        }
        break;
        case 2:
        system("clear");
        fp=fopen("RestaurantBill.dat","r");
        printf("\n *******Your Previous Invoices*********\n");
        while (fread(&od,sizeof(struct orders),1,fp))
        {
            float tot=0;
            generateBillHeader(od.customer,od.date);
            for (int i = 0; i < od.numOfItems; i++)
            {
                generateBillBody(od.itm[i].item,od.itm[i].qty,od.itm[i].price);
                tot+=od.itm[i].qty*od.itm[i].price;
            }
            generateBillFooter(tot);
            
        }
        fclose(fp);
        break;
    case 3:
    printf("\n Enter the name of the custumer");
   // fgetc(stdin);
    fgets(name,20,stdin);
    name[strlen(name)-1]=0;
    system("clear");
        fp=fopen("RestaurantBill.dat","r");
        printf("\n *******Invoice of %s*********",name);
        while (fread(&od,sizeof(struct orders),1,fp))
        {
            float tot=0;
            if (!strcmp(od.customer,name))
            {
                generateBillHeader(od.customer,od.date);
            for (int i = 0; i < od.numOfItems; i++)
            {
                generateBillBody(od.itm[i].item,od.itm[i].qty,od.itm[i].price);
                tot+=od.itm[i].qty*od.itm[i].price;
            }
            generateBillFooter(tot); 
            invoiceFound=1;
            }   
        }
        if (!invoiceFound)
        {
            printf("Sorry the invoice for %s does not exist",name);
        }
        
        fclose(fp);
        break;
           
    case 4:
    printf("\n\t\t ******Good Bye*****   ");
    exit(0);
    break;
    default:
    printf("\n Sorry invalide operation");
        break;
    }
    printf("Do you want to perform another operation ?[Y/N]");
    scanf("%s",&contFlag);}
    printf("\n\t\t ******Good Bye*****   ");









}