#include <iostream>
#include <string>
#include <fstream>


using namespace std;

struct student {
    string surname;
    string name;
    string middle;
    string date;
    string number_group;
    float gpa;
    string sex;
    student *next;
} *head;



void AddStudent(student *&ph, student *&pt, string surname, string name,string middle, string date, string number_group, float gpa, string sex) {
      	student *t=new student;
      	t->surname=surname;t->name=name;t->middle=middle;t->date=date;t->number_group=number_group;t->gpa=gpa;t->sex=sex;
        t->next=NULL;
        if (ph==NULL) ph=pt=t; else pt=pt->next=t;
}	

void PrintStudent(student *ph) {
       if (ph==NULL) {
       cout<<"Queque clear";
       }
       while (ph!=NULL) {
       cout<<ph->surname<<" "<<ph->name<<" "<<ph->middle<<" "<<ph->date<<" "<<ph->number_group<<" "<<ph->gpa<<" "<<ph->sex;
       cout<<endl; ph=ph->next;
       }
       cout<<endl; 
}
void SerialStudent(student *ph) {
       ofstream fout("dump.bin",ios::binary);
       while (ph!=NULL) {
       fout<<ph->surname<<" "<<ph->name<<" "<<ph->middle<<" "<<ph->date<<" "<<ph->number_group<<" "<<ph->gpa<<" "<<ph->sex;
       fout<<endl; ph=ph->next;
       }
       cout<<endl; 
}

void FindStudent (student *ph,string surname,string name,string number_group) {
	int k=1;
	while(ph!=NULL) {
        if (ph->surname==surname && ph->name==name && ph->number_group==number_group)  {
        cout<<"Номер:"<<k<<" "<<"Фамилия:"<<ph->surname<<" "<<"Имя:"<<ph->name<<endl; 
	    return;
	    } 
	    ph=ph->next;	k++;
        }
        cout<<"-1"<<endl;
    return;
}

void DeleteStudent(student *&ph,int n) {
	
	student *t1=ph;
	if (n==1) {
	ph=t1->next;
	delete t1;
	return;
	}
	for (int i=1;i<n-1;++i) {
	t1=t1->next;
	if ((t1==NULL) || (t1->next==NULL)) {
	cout<<"Error";
        cout<<endl;
	return;
	}
	}
	student *t2=t1->next;
	t1->next=t2->next;
	delete t2;
	return;
}


void SortStudent(student *ph) { //параметр - указатель на начало списка.

	student *p=new student; 
	student *pp=new student;
	for (student *p = ph; p!= NULL; p=p->next)
	for (student *pp = ph; pp->next!=NULL; pp=pp->next)
	if (pp->surname > pp->next->surname) {
	swap(pp->surname,(pp->next)->surname);
	swap(pp->name,(pp->next)->name);
	swap(pp->middle,(pp->next)->middle);
	swap(pp->date,(pp->next)->date);
	swap(pp->number_group,(pp->next)->number_group);
	swap(pp->gpa,(pp->next)->gpa);
	swap(pp->sex,(pp->next)->sex);           
	}
	else if ((pp->surname == pp->next->surname) && (pp->name>pp->next->name)) {
	swap(pp->surname,(pp->next)->surname);
	swap(pp->name,(pp->next)->name);
	swap(pp->middle,(pp->next)->middle);
	swap(pp->date,(pp->next)->date);
	swap(pp->number_group,(pp->next)->number_group);
	swap(pp->gpa,(pp->next)->gpa);
	swap(pp->sex,(pp->next)->sex);           
	}
}

//8.	Очередь. Функция для отчисления всех студентов, чей контрольный срок ниже введённого значения.
/*
void otchislenie(student *&ph,float gpa) {
       while(ph!=NULL)  {
       if (gpa>ph->gpa)
       cout<<ph->surname<<" "<<ph->name<<" "<<ph->middle<<" "<<ph->date<<" "<<ph->number_group<<" "<<ph->gpa<<" "<<ph->sex;
       cout<<endl;ph=ph->next;
       }
     }
*/
            
int main() {
    system("CLS");
    setlocale(0,"RUS");
    //ifstream fin("out");
    //ofstream fout("out",ios::binary);
    
    string surname,name,middle,date,number_group,sex;
    float gpa; 
    student *t=new student;
    student *ph=NULL;
    student *pt=NULL;  // ph-nachalo, pt-kones;
    //struct student *p;
    int variant=0;
    bool flag = true;
    while (1) {
	   
    cout << "Выберите вариант\n" << endl;
    cout << "1. Добавить\n"
         << "2. Посмотреть\n"
         << "3. Поиск по фамилии имени и группы\n"
         << "4. Удалить студента по номеру\n"
         << "5. Сортировка по фамилии и имени\n"
	 << "6. Сериализация\n"
         << "7. Выйти\n" << endl;
    cout << "Выберите действие\n"<<endl;
    cin>>variant;
    system("CLS");
    switch ( variant ) {
         case 1: 
             while (flag) {
             cout<<"Добавить студента:"<<endl;
	     cout<<"Фамилия, имя, отчество, дата рождения, номер группы, средний балл, пол"<<endl;
             cin>>surname; if (surname =="end") { break; }
             cin>>name>>middle>>date>>number_group>>gpa>>sex;
             AddStudent(ph,pt,surname,name,middle,date,number_group,gpa,sex);
	     //fout<<surname<<" "<<name<<" "<<middle<<" "<<date<<" "<<number_group<<" "<<gpa<<" "<<sex<<endl;
	     cout<<"Студент добавлен"<<endl;
	     cout<<endl;	
             }
             system("CLS");        	
	     break; 
        case 2:
	     cout<<endl;	
             PrintStudent(ph);
	     /*
	     for (string line; getline(fin, line);) {
    	     cout<<line;
	     cout<<endl; 
	     }
             cout<<endl;
	     fin.close();
	     */  
             break;
        case 3:	
             cout <<"Поиск по фамилии, имени и группе: "<<endl;
             cin >> surname >> name >> number_group; 
             FindStudent(ph,surname,name,number_group);
             break;                                         
        case 4:
	     
             cout <<"Номер студента: ";
             int n;
	     cin>>n;
             cout<<endl;
             DeleteStudent(ph,n);
             break;
        case 5:
             cout<<"Сортировка по фамилии и имени"<<endl;
	     SortStudent(ph);  
             break;    
        case 6:
	     SerialStudent(ph);
	     cout<<"Сериализация выполнена успешно"<<endl;
	     break;
	case 7:
	     cout<<"Пока пока!"<<endl;
             exit(EXIT_SUCCESS);	
        default:
             cout<<"Вы выбрали неверный вариант";
}
}
    system("PAUSE");
    return 0;
}
