#include <vcl.h>
#pragma hdrstop
#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}
double **TForm1::create(int m,int n)
{
	double **mas;
	mas=new double*[m];
	for(int i=0;i<m;i++)
		mas[i]=new double[n];
	return mas;
}
void TForm1::del(double**mas, int m)
{
	for(int i=0;i<m;i++)
	{
		delete mas[i];
	}
	delete mas;
}
int TForm1::MandN(FILE*out, int&m, int&n)
{
	int c; n=0; m=0; double k=0;
	char h;
	while((c=int(h=fgetc(out)))!=int('\n'))
	{
		if((c==int('0'))||(c==int('1'))||(c==int('2'))||(c==int('3'))||
		(c==int('4'))||(c==int('5'))||(c==int('6'))||(c==int('7'))||(c==int('8'))
		||(c==int('9'))||(c==int('-')))
		{
			fseek(out, -1,SEEK_CUR);
			fscanf(out, "%lf",&k);
			m++;
		}
		if(c==EOF)
		{n++;fseek(out,0,SEEK_SET); return 0;}
	}
	fseek(out,0,SEEK_SET);
			char*f;
			f=(char *)malloc(1000*sizeof(char));
			while(fgetc(out)!=EOF)
			{
				fseek(out,-1,SEEK_CUR);
				fgets(f,1000,out);
				n++;
			}
		 free(f);
		 fseek(out,0,SEEK_SET);
		 return 1;

}
void TForm1::add_matr(double **a, double **b, double **c, int m, int n)
{
	for(int i=0;i<m;i++)
	{
		for(int j=0;j<n;j++)
		{
			c[i][j]=a[i][j]+b[i][j];
		}
	}

}
bool TForm1::read_matr(AnsiString FileName, double **a, int &m, int &n)
{
	FILE *out=fopen(FileName.c_str(),"rt");
	if(out)
	{
		for(int i=0;i<m;i++)
		for(int j=0;j<n;j++)
		fscanf(out,"%lf",&a[i][j]);
		fclose(out);
		return true;
	}
	return false;
}
bool TForm1::write_matr(AnsiString FileName, double **a, int &m, int &n)
{
	FILE *out=fopen(FileName.c_str(),"rt");
	if(out)
	{
		for(int i=0;i<m;i++)
		for(int j=0;j<n;j++)
		fprintf(out,"%lf",a[i][j]);
		fclose(out);
		return true;
	}
	return false;
}
void TForm1::Mult_matr(double ch, double **a, int m, int n)
{
	for(int i=0;i<m;i++)
	{
		for(int j=0;j<n;j++)
		{
			a[i][j]*=ch;
        }
    }
}
void TForm1::Product_matr(double **a, double **b, double **c, int m, int n)
{
	for(int i=0;i<m;i++)
	{
		for(int j=0;j<n;j++)
		{
			for(int k = 0;k<n;k++)
			{
				c[i][k]=a[i][j]*b[j][k];
            }
        }
    }
}
void TForm1::fill_matr(double **a, int m, int n)
{
	for(int i=0;i<m;i++)
	{
		for(int j=0;j<m;j++)
		{
			a[i][j] = rand()%20+1;
		}
	}

}
bool TForm1::CheckShod(double **a, int n)
 {
	int h=0;
	for(int i=0;i<n;i++)
	{
	double ad=0;
		for(int j=0;j<n;j++)
		{
			if(i==j)
				continue;
			else
				ad+=abs(a[i][j]);//����� ������� ��������� ������, i != j
		}
		if(abs(a[i][i])>ad)
		h++;
	}
	if(h==n)
	return true;
	else
	return false;
 }
double TForm1::norm(int m,double *pr)
 {
     double norm = 0;
	for (int i = 0; i < m; i++)
	{
	norm += pow(pr[i],2);
	}
		norm=sqrt(norm);
	return norm;
 }
 //---------------------------------------------------------------------------
int m ,n; // ���������� ����������� �������
double **a; // �������� ������� �������
double *b; // ������ ������� b
double *bet ; // ����� ������� ����
double **alph; // ����� �������
double *x;//������� ������� ����������
double *pr;//���������� �������
//---------------------------------------------------------------------------
void __fastcall TForm1::Button1Click(TObject *Sender)//��������� ������ ��� ������� � ������ �������
{                                                    //������ ������� � ������� ������� b,												 //����� ������ � ������� ������� �� �����
   Memo1->Lines->Clear();
   Memo2->Lines->Clear();

	if(OpenDialog1->Execute())
	{
		Memo1->Lines->LoadFromFile(OpenDialog1->FileName);//������� ������� �� �����
		FILE *in = fopen(AnsiString(OpenDialog1->FileName).c_str(),"rt");
		MandN(in,m,n);// ������� ���������� ����� � ��������
        fclose(in);
		a = create(m,n); //��������� ������ ��� ������� �
		read_matr(OpenDialog1->FileName, a,m, n);//��������� ������� �� ����� � �

	}
	if(OpenDialog1->Execute())
	{
	 Memo2->Lines->LoadFromFile(OpenDialog1->FileName);//����� ������� ������� b �� �����
	 b = new double[m];//�������� ������ ��� ������ �������
	 FILE *out=fopen(AnsiString(OpenDialog1->FileName).c_str(),"rt");
		if(out)
		{
			for(int i=0;i<n;i++)//��������� ������ ������� b �� ����� � ������
			fscanf(out,"%lf",&b[i]);
			fclose(out);
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button2Click(TObject *Sender)  //�������� ������� �� ����������
{
Edit1->Text=IntToStr(m);
Edit4->Text=IntToStr(n);
	   if(CheckShod(a,n))// �������� ������� ����������
			Edit3->Text = "������� ��������";
		else
			Edit3->Text = "������� �� ��������";
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button3Click(TObject *Sender)
{
   Memo3->Lines->Clear();
bet = new double [m]; //��������� ������ ��� ������ ������� ����
alph = create(m,m);//��������� ������ ��� ����� �������
x=new double [m]; //��������� ������ ��� ������ ������� x
pr = new double[m];//��������� ������ ��� ������ �-�� ��������
int  kron;

   for(int i = 0;i<m;i++)//���� �������� ����� ������� � ������� ������� ����
   {
	   for(int j = 0; j<m;j++)
	   {
		   if(i==j)//������ ���������
		   kron=1;
		   else
		   kron=0;
		   alph[i][j] = -(a[i][j]/a[i][i])*(1-kron);//������� ����� �������
		   bet[i] = b[i]/a[i][i];//������� ������� ������� ����
	   }
   }
   double P = StrToFloat(Edit2->Text);//���������� ����������� �� ����
   for(int i=0;i<m;i++)
   {
	x[i]=1.0; //������� ��������� �����������
   }
//!--------------------------------������� ������� ������� x------------------!
 double res=0;
  do
   {
       for(int i=0;i<m;i++)
		{
		res=bet[i];
			for(int j=0;j<i;j++)
			{
				res+=alph[i][j]*x[j];
			}
			for(int j=i+1;j<n;j++)
			{
				res+=alph[i][j]*x[j];
			}
			pr[i]=abs(x[i]-res);
			x[i]=res;
		}
	norm(m,pr);
   }
while(norm(m,pr)>P);
//!----------------------------------����� �������----------------------------!
	 for(int i=0;i<m;i++)
   {
	AnsiString buf="";
	buf+="x["+AnsiString(i)+"] = " + AnsiString(x[i]);

	Memo3->Lines->Add(buf);

   }
}
