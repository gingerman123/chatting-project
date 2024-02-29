#pragma once
#include "client.h"
//using namespace std;


namespace Project1 {


	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace Socket_cli;

	/// <summary>
	/// MyForm에 대한 요약입니다.
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: 생성자 코드를 여기에 추가합니다.
			//
		}

		MyForm(client^ clnt)
		{

			InitializeComponent();
			_clnt = clnt;
			_clnt->MyEvent += gcnew Action<String^>(this, &MyForm::ReceivedMsg);
			this->AcceptButton = button1;

		}

	private: client^ _clnt;

	protected:
		/// <summary>
		/// 사용 중인 모든 리소스를 정리합니다.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}

		~MyForm()
		{
			if (_clnt != nullptr) {
				// MyEvent 이벤트 핸들러를 해제
				_clnt->MyEvent -= gcnew Action<String^>(this, &MyForm::ReceivedMsg);

				// _my를 삭제
				delete _clnt;
				_clnt = nullptr;  // nullptr로 설정하여 dangling pointer를 방지
			}
			if (components)
			{
				delete components;
			}
			
		}

	private: System::Windows::Forms::Label^ label1;
	protected:
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::TextBox^ textBox1;
	private: System::Windows::Forms::TextBox^ textBox2;
	private: System::Windows::Forms::Label^ label2;
	private:
		/// <summary>
		/// 필수 디자이너 변수입니다.
		/// </summary>
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// 디자이너 지원에 필요한 메서드입니다. 
		/// 이 메서드의 내용을 코드 편집기로 수정하지 마세요.
		/// </summary>
		void InitializeComponent(void)
		{
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(127, 98);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(18, 15);
			this->label1->TabIndex = 0;
			this->label1->Text = L"id";
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(390, 80);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(87, 91);
			this->button1->TabIndex = 1;
			this->button1->Text = L"button1";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(168, 95);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(156, 25);
			this->textBox1->TabIndex = 2;
			// 
			// textBox2
			// 
			this->textBox2->Location = System::Drawing::Point(168, 146);
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(156, 25);
			this->textBox2->TabIndex = 4;
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(127, 149);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(25, 15);
			this->label2->TabIndex = 3;
			this->label2->Text = L"pw";
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 15);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(611, 311);
			this->Controls->Add(this->textBox2);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->label1);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			this->ResumeLayout(false);
			this->PerformLayout();
		}

#pragma endregion
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
		button1->NotifyDefault(false);
		SendMessageForm();
	}
	private: System::Void MyForm_Load(System::Object^ sender, System::EventArgs^ e) {

	}

	public: void SendMessageForm()
	{
		String^ tmptxt_1 = textBox1->Text; // textBox는 해당 텍스트 상자의 이름입니다.
		String^ tmptxt_2 = textBox2->Text; // textBox는 해당 텍스트 상자의 이름입니다.
		String^ buffer = tmptxt_1 + " " + tmptxt_2;
		_clnt->SendMessage(buffer);
	}

	public: void ReceivedMsg(String^ message)
	{
		String^ inputString = message;

		array<String^>^ subString = inputString->Split(' ');

		String^ index_s = subString[0];
		String^ isTrue = subString[1];
		int index = Int32::Parse(index_s);

		
		if (isTrue == "true")
		{
			this->Invoke(gcnew MethodInvoker(this, &MyForm::MainFormShow));

		}
		else
		{
			System::Windows::Forms::MessageBox::Show("Check the ID and Password", "warning", MessageBoxButtons::OK, MessageBoxIcon::Warning);
		}
	
	}

	public: void MainFormShow() {

	}

	};
}