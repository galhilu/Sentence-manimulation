#include <stdio.h>
#include <string.h>
#include <stdlib.h>


void printmenu(){
    printf("******** Main menu ********\n\n");
    printf("1 :  Input the sentence\n");
    printf("2 :  Print the sentence\n");
    printf("3 :  Reverse the sentence\n");
    printf("4 :  Rotate left N\n");
    printf("5 :  Rotate right N\n");
    printf("6 :  Sort the sentence\n");
    printf("7 :  Search the word\n");
    printf("8 :  Count number of words\n");
    printf("9 :  Display substring M\n");
    printf("10 : Quit\n");
    printf("\n****************************\n");
    printf("\nPlease, enter your choice>\n");
}
void inputSent(char str_in[],int k,char str_out[],int n){
    char *new_str = (char*)malloc(n+1);
    if (new_str==NULL){
        printf("Memory allocation failed\n");
        exit(1);
    }
    if (k<=n)
        strcpy((char*)new_str, str_in);



    printf("%s",str_in);

}
void printSent(char str[],int n) {
    printf("%s", str);
}
int emptySent(char str[]) {
    if (str[0] == 'a'){
        printf("ERROR: The sentence is empty.\n");
        return 1;
    }
    return 0;
}
void stripspace(char *p,int n){
    int i=0,j=0;
    while (*(p+i)==' ')
        i++;
    *(p+j)=*(p+i);
    while (i<=n){
        while (*(p+i)==' '&& *(p+i+1)==' ')
            i++;
        *(p+j)=*(p+i);
        i++;
        j++;
    }
    if(*(p+n)==' ')
        *(p+n)='\0';
    return;
}
int checkAZ(char str[]){
    int i=0;
    int j;
    while (str[i]!='\0'){
        if(!((str[i]>64&&str[i]<91)||str[i]==' '))
            return 1;
        i++;
    }
    for(j=0; j<=strlen(str); j++){
        if(str[j]!=' ')
            return 0;
    }
    return 1;
}
int checkChars( char str[]){
    char s[100];
    strcpy(s,str);
    if (strlen(s) < 31)
        return 1;
    return 0;

}
int countWords (char str []){
    int i=0,c=0;
    while (str[i]!='\0'){
        if(str[i]==' ')
            c++;
        i++;
    }
    return c+1;
}
int maxWordLength(char str[]){
    int l=0,i=0,max=0;
    while (str[i]!='\0'){
        if((str[i]>64&&str[i]<91))
            l++;
        if(str[i]==' '){
            if(max<l)
                max=l;
            l=0;
        }
        i++;
    }
    if(max<l)
        max=l;
    return max;
}

void revSent(char str[]){
    int last=0;
    last = strlen(str)-1;
    char * str2 = (char *) malloc(last+2);
    int counter=0;

    for (int i=last; i>=0; --i){
        if (str[i]==' '){
            for (int j=i+1; j<=last; ++j){
                *(str2+counter) = str[j];
                counter++;
            }
            *(str2+counter) = ' ';
            counter++;
            last = i-1;
        }

        if (i == 0){
            for (int j=i; j<=last; ++j){
                *(str2+counter) = str[j];
                counter++;
            }
        }
    }
    *(str2+counter) = '\0';
    strcpy(str, (char *)str2);
    free(str2);
    return;
}
void sort(char str[],char mode){
    char cmp1[30],cmp2[30];
    int i=0,c=0,start=0,j,s=0;
    while (str[i]!='\0'){       //more then 1 word?
        if(str[i]==' ')
            c=1;
        i++;
    }
    if (c==0)                   //if 1 word then done
        return;
    do {
        s = 0;
        i = 0;
        start=0;
        while (str[i] != '\0') {
            i= start;
            while (str[i] != ' ') {
                cmp1[i-start] = str[i];
                i++;
            }
            cmp1[i-start] = '\0';
            i++;
            while (str[i] != ' '&&str[i] != '\0') {
                cmp2[i - strlen(cmp1)-1-start] = str[i];
                i++;
            }
            cmp2[i - strlen(cmp1)-1-start] = '\0';    //-1 for space between words
            if (strcmp(cmp1, cmp2) > 0) {            //need to switch?
                for (j = 0; j < strlen(cmp2); j++)
                    str[start + j] = cmp2[j];
                str[start + j] = ' ';

                for (j = 0; j < strlen(cmp1); j++)
                    str[start + strlen(cmp2)+1 + j] = cmp1[j];
                if (str[start + strlen(cmp2)+1 + j]!='\0')
                    str[start + strlen(cmp2)+1 + j] = ' ';
                start= i-strlen(cmp1);
                s = 1;                        // a flag that a switch was made
            } else
                start= i-strlen(cmp2);
        }
    }while (s!=0);
    if (mode=='D')
        revSent(str);
    return;
}
void rolSent(char str[], int m) {
    int i, k, j, size = 0;
    int r = 0;
    int l = 0;
    int c = 0;
    int idx = 0;
    size = strlen(str);
    char *left, *right;
    for (i = 0; i < size; i++) {
        if (str[i] == ' ') {
            c++;
            if (c <= m) {
                idx = i;
            }
        }
    }
    left = (char*)malloc(size-idx+1);
    right = (char*)malloc(idx+1);
    for (i = idx + 1; str[i] != '\0'; i++) {
        *(left+l) = str[i];
        l++;}
    *(left+l) = ' ';
    *(left + l + 1) = '\0';
    for (k = 0; k < idx; k++) {
        *(right+k) = str[k];
        r++;
    }
    *(right + r) = '\0';
    left = (char*)realloc(left, (size+1));
    strcat((char*)left, (char*)right);
    free(right);
    strcpy(str, (char*)left);
    free(left);
}
void rorSent(char str[], int m) {
    rolSent(str, countWords(str) - m);
}


void subsent(char str[],int k){
    int i=0,j=0,s=0,c=0,b=0;
    char sub[30][30];
    for (i=0;i<=30;i++)
        strcpy(sub[i],"a");      //putting default string in all
    char temp[30];
    temp[k]='\0';
    char pstr[30];
    i=0;
    while (str[i]!='\0'){                //striping spaces
        if(str[i]==' '){
            i++;
            continue;}
        pstr[j]=str[i];
        i++;
        j++;
    }
    pstr[j]='\0';
    i=0;
    while (pstr[i+k-1]!='\0'){
        for(j=0;j<k;j++)       //create a sub string
            temp[j]=pstr[(i+j)%strlen(pstr)];
        for(s=0;s<=i;s++){
            if(strcmp(sub[s],temp)==0)
                c++;                 //flag for if string is already present
        }
        if(c==0) {
            strcpy(sub[i-b], temp);
        }
        if(c!=0)
            b++;
        c=0;
        i++;
    }
    s=0;
    while(sub[s][0]!='a'){
        printf("%s\n",sub[s]);
        s++;
    }

}
int secnum(char x[]){
    int m;
    m=x[2]-48;
    if (x[3]>=48&&x[3]<=57)
        m=m+(x[4]-48)*10;
    return m;
}
void search(char str[],char word[]){
    int i=0,j=0,wn=1;
    char temp[30];
    while (str[i]!='\0'){
        while (str[i]!=' '&&str[i]!='\0'){
            temp[j]=str[i];
            i++;
            j++;
        }
        temp[j]='\0';
        if (strcmp(word,temp)==0){
            printf("The word %s is placed in the %d place.\n",word,wn);
            return;
        }
        wn++;
        i++;
        j=0;
    }
    printf("The word %s is not found.\n",word);
    return;
}
int main() {
    char x[10]="0";
    char str[101]="a";
    int m,i;
    char**wordarry;
    int n= strlen(str);
    int wordnum;
    char word[31];
    int max = 0;
    while (1) {
        printmenu();
        scanf(" %[^\n]",x);
        if (x[0] == '1'&&x[1] == '\0') {
            while (1) {
                printf("Please, enter your sentence>\n");
                scanf(" %[^\n]",str);
                if(strlen(str)>30 || checkAZ(str)==0 && checkChars(str)==1)
                    break;
                printf("ERROR: Incorrect data, try again.\n");
                strcpy(str, "a");
                while ((getchar()) != '\n');
            }
            printf("%s\n",str);
            n=strlen(str);
            stripspace(str,n);
            strcpy(x,"0");
            continue;
        }

        if (x[0] == '2'&&x[1] == '\0'){
            if(emptySent(str)){
                while ((getchar()) != '\n');
                strcpy(x,"0");
                continue;}
            printf("%s\n",str);
            strcpy(x,"0");
            continue;
        }

        if(x[0] == '3'&&x[1] == '\0'){
            if(emptySent(str)){
                while ((getchar()) != '\n');
                strcpy(x,"0");
                continue;}
            revSent(str);
            printf("%s\n", str);
            strcpy(x,"0");
            continue;
        }

        if (x[0] == '4') {
            if (emptySent(str)) {
                while ((getchar()) != '\n');
                strcpy(x, "0");
                continue;
            }
            n = secnum(x);
            max = countWords(str);
            if (n > max) {
                printf("ERROR: Incorrect command, try again.\n");
                continue;
            }

            if (n == max) {
                printf("%s\n", str);
                continue;
            }
            rolSent(str, n);
            printf("%s\n", str);
            continue;
        }

        if (x[0] == '5') {
            if (emptySent(str)) {
                while ((getchar()) != '\n');
                strcpy(x, "0");
                continue;
            }
            n = secnum(x);
            max = countWords(str);
            if (n > max) {
                printf("ERROR: Incorrect command, try again.\n");
                continue;
            }

            if (n == max) {
                printf("%s\n", str);
                continue;
            }
            rorSent(str, n);
            printf("%s\n", str);
            continue;
        }

        if (x[0]=='6'){
            if(x[2]=='D')
                sort(str,'D');
            if(x[2]=='A'||x[2]=='\0')
                sort(str,'A');
            printf("%s\n",str);
            strcpy(x,"0");
            continue;
        }

        if (x[0]=='7'){
            if(emptySent(str)){
                while ((getchar()) != '\n');
                strcpy(x,"0");
                continue;}
            if(x[1]==' '&&(x[i]>64&&x[i]<91)){
                printf("ERROR:Incorrect command, try again.");
            }
            i=2;
            while((x[i]>64&&x[i]<91)||(x[i]==' ')) {
                word[i - 2] = x[i];
                i++;
            }
            word[i-2]='\0';
            search(str,word);
            strcpy(x,"0");
            continue;
        }

        if (x[0] == '8'&&x[1] == '\0'){
            if(emptySent(str)){
                while ((getchar()) != '\n');
                strcpy(x,"0");
                continue;}
            printf("The number of words in the sentence is %d\n", countWords(str));
            strcpy(x,"0");
            continue;
        }

        if(x[0] == '9'){
            if(emptySent(str)){
                while ((getchar()) != '\n');
                strcpy(x,"0");
                continue;}
            m= secnum(x);
            if (!(m>0&&m<= maxWordLength(str))){
                printf("Incorrect command, try again.");
                strcpy(x,"0");
                continue;
            }
            subsent(str,m);
            strcpy(x,"0");
            continue;
        }

        if(x[0] =='1'&&x[1]=='0'&&x[2] == '\0')
            break;
        while ((getchar()) != '\n');
        printf("Incorrect command, try again.\n");
        strcpy(x,"0");

    }
    return 0;
}
