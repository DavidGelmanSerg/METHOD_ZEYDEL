//---------------------------------------------------------------------------
#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Dialogs.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TMemo *Memo1;
	TButton *Button1;
	TButton *Button2;
	TEdit *Edit1;
	TEdit *Edit2;
	TEdit *Edit3;
	TLabel *Label1;
	TLabel *Label2;
	TLabel *Label3;
	TOpenDialog *OpenDialog1;
	TButton *Button3;
	TMemo *Memo2;
	TLabel *Label4;
	TLabel *Label5;
	TMemo *Memo3;
	TLabel *Label6;
	TButton *Button4;
	TLabel *Label7;
	TEdit *Edit4;
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall Button3Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
    double**create(int m, int n); //��������� ������ ��� �������
	void del(double**mas, int m); // ������������ ���������� ������
	int MandN(FILE*out, int&m, int&n); //������� ���������� �������� � ����� ������� ������ �����
	bool read_matr(AnsiString FileName, double **a, int &m, int &n); // ������ ������� �� �����
	bool write_matr(AnsiString FileName, double **a, int &m, int &n); //������ ������� � ����
	void add_matr(double **a, double **b, double **c, int m, int n);  // �������� ������
	void Mult_matr(double ch, double **a, int m, int n); //��������� ������� �� �����
	void Product_matr(double **a, double **b, double **c, int m, int n); //��������� ������
	void fill_matr(double **a, int m, int n); // ���������� �������
	bool CheckShod(double **a, int n);// �������� �� ����������
	double norm(int m,double *pr);//����� �������
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
