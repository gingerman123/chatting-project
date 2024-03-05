#pragma once
#include"client.h"
namespace Project1 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace Socket_cli;

	/// <summary>
	/// newForm에 대한 요약입니다.
	/// </summary>
	public ref class newForm : public System::Windows::Forms::Form
	{
	private:
	public:
		newForm(void)
		{
			InitializeComponent();
			//
			//TODO: 생성자 코드를 여기에 추가합니다.
			//
		}
		newForm(client^ clnt)
		{

			InitializeComponent();
			_clnt = clnt;
			_clnt->MyEvent += gcnew Action<String^>(this, &newForm::ReceivedMsg);
			//this->AcceptButton = button1; //엔터키?

		}

	protected:
		/// <summary>
		/// 사용 중인 모든 리소스를 정리합니다.
		/// </summary>
		~newForm()
		{
			if (_clnt != nullptr) {
				// MyEvent 이벤트 핸들러를 해제
				_clnt->MyEvent -= gcnew Action<String^>(this, &newForm::ReceivedMsg);

				// _my를 삭제
				delete _clnt;
				_clnt = nullptr;  // nullptr로 설정하여 dangling pointer를 방지
			}
			if (components)
			{
				delete components;
			}

		}
	private: String^ gender;
	private: client^ _clnt;
	private: System::Windows::Forms::Label^ label1;
	protected:
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::CheckBox^ checkBox1;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::Label^ label5;
	private: System::Windows::Forms::Label^ label6;
	private: System::Windows::Forms::Label^ label7;
	private: System::Windows::Forms::TextBox^ textBox1;


	private: System::Windows::Forms::Panel^ panel1;
	private: System::Windows::Forms::Panel^ panel2;
	private: System::Windows::Forms::TextBox^ textBox2;
	private: System::Windows::Forms::Panel^ panel3;
	private: System::Windows::Forms::TextBox^ textBox3;
	private: System::Windows::Forms::Panel^ panel4;
	private: System::Windows::Forms::TextBox^ textBox4;
	private: System::Windows::Forms::Panel^ panel5;
	private: System::Windows::Forms::TextBox^ textBox5;

	private: System::Windows::Forms::Button^ button2;
	private: System::Windows::Forms::Button^ button3;
	private: System::Windows::Forms::Label^ label8;

	private: System::Windows::Forms::CheckBox^ checkBox2;

	private: System::Windows::Forms::RadioButton^ radioButton1;
	private: System::Windows::Forms::RadioButton^ radioButton2;
	private: System::Windows::Forms::CheckBox^ checkBox3;
	private: System::Windows::Forms::Label^ label9;
	private: System::Windows::Forms::DateTimePicker^ dateTimePicker1;
	private: System::Windows::Forms::Button^ botton_Exit;
	private: System::Windows::Forms::Label^ label10;
	private: System::Windows::Forms::Label^ label11;
	private: System::Windows::Forms::Label^ label12;
	private: System::Windows::Forms::Label^ label13;
	private: System::Windows::Forms::Label^ label14;
	private: System::Windows::Forms::Label^ label15;
	private: System::Windows::Forms::Label^ label16;
	private: System::Windows::Forms::Label^ label17;
	private: System::Windows::Forms::Label^ label18;
	private: System::Windows::Forms::Label^ label19;



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
			this->checkBox1 = (gcnew System::Windows::Forms::CheckBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->panel2 = (gcnew System::Windows::Forms::Panel());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->panel3 = (gcnew System::Windows::Forms::Panel());
			this->textBox3 = (gcnew System::Windows::Forms::TextBox());
			this->panel4 = (gcnew System::Windows::Forms::Panel());
			this->textBox4 = (gcnew System::Windows::Forms::TextBox());
			this->panel5 = (gcnew System::Windows::Forms::Panel());
			this->textBox5 = (gcnew System::Windows::Forms::TextBox());
			this->dateTimePicker1 = (gcnew System::Windows::Forms::DateTimePicker());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->checkBox2 = (gcnew System::Windows::Forms::CheckBox());
			this->radioButton1 = (gcnew System::Windows::Forms::RadioButton());
			this->radioButton2 = (gcnew System::Windows::Forms::RadioButton());
			this->checkBox3 = (gcnew System::Windows::Forms::CheckBox());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->botton_Exit = (gcnew System::Windows::Forms::Button());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->label11 = (gcnew System::Windows::Forms::Label());
			this->label12 = (gcnew System::Windows::Forms::Label());
			this->label13 = (gcnew System::Windows::Forms::Label());
			this->label14 = (gcnew System::Windows::Forms::Label());
			this->label15 = (gcnew System::Windows::Forms::Label());
			this->label16 = (gcnew System::Windows::Forms::Label());
			this->label17 = (gcnew System::Windows::Forms::Label());
			this->label18 = (gcnew System::Windows::Forms::Label());
			this->label19 = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 13.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(129)));
			this->label1->Location = System::Drawing::Point(325, 25);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(97, 29);
			this->label1->TabIndex = 0;
			this->label1->Text = L"회원가입";
			// 
			// button1
			// 
			this->button1->Enabled = false;
			this->button1->FlatAppearance->BorderSize = 2;
			this->button1->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(129)));
			this->button1->ForeColor = System::Drawing::Color::DarkRed;
			this->button1->Location = System::Drawing::Point(304, 585);
			this->button1->Margin = System::Windows::Forms::Padding(3, 4, 3, 4);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(130, 56);
			this->button1->TabIndex = 1;
			this->button1->Text = L"가입하기";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &newForm::button1_Click);
			// 
			// checkBox1
			// 
			this->checkBox1->AutoSize = true;
			this->checkBox1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(129)));
			this->checkBox1->Location = System::Drawing::Point(281, 525);
			this->checkBox1->Margin = System::Windows::Forms::Padding(3, 4, 3, 4);
			this->checkBox1->Name = L"checkBox1";
			this->checkBox1->Size = System::Drawing::Size(172, 22);
			this->checkBox1->TabIndex = 2;
			this->checkBox1->Text = L"모든 규정에 동의합니다.";
			this->checkBox1->UseVisualStyleBackColor = true;
			this->checkBox1->CheckedChanged += gcnew System::EventHandler(this, &newForm::checkBox1_CheckedChanged);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10));
			this->label2->Location = System::Drawing::Point(101, 120);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(86, 20);
			this->label2->TabIndex = 3;
			this->label2->Text = L"사용할 아이디";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10));
			this->label3->Location = System::Drawing::Point(112, 173);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(57, 20);
			this->label3->TabIndex = 4;
			this->label3->Text = L"비밀번호";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10));
			this->label4->Location = System::Drawing::Point(101, 227);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(86, 20);
			this->label4->TabIndex = 5;
			this->label4->Text = L"비밀번호 확인";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10));
			this->label5->Location = System::Drawing::Point(125, 279);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(33, 20);
			this->label5->TabIndex = 6;
			this->label5->Text = L"이름";
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10));
			this->label6->Location = System::Drawing::Point(124, 389);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(33, 20);
			this->label6->TabIndex = 7;
			this->label6->Text = L"생일";
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10));
			this->label7->Location = System::Drawing::Point(111, 436);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(45, 20);
			this->label7->TabIndex = 8;
			this->label7->Text = L"닉네임";
			// 
			// textBox1
			// 
			this->textBox1->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(220)),
				static_cast<System::Int32>(static_cast<System::Byte>(47)));
			this->textBox1->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->textBox1->Location = System::Drawing::Point(233, 120);
			this->textBox1->MaxLength = 50;
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(248, 18);
			this->textBox1->TabIndex = 9;
			this->textBox1->TextChanged += gcnew System::EventHandler(this, &newForm::textBox1_TextChanged);
			// 
			// panel1
			// 
			this->panel1->BackColor = System::Drawing::SystemColors::ControlText;
			this->panel1->Location = System::Drawing::Point(231, 144);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(249, 1);
			this->panel1->TabIndex = 16;
			// 
			// panel2
			// 
			this->panel2->BackColor = System::Drawing::SystemColors::ControlText;
			this->panel2->Location = System::Drawing::Point(231, 198);
			this->panel2->Name = L"panel2";
			this->panel2->Size = System::Drawing::Size(249, 1);
			this->panel2->TabIndex = 18;
			// 
			// textBox2
			// 
			this->textBox2->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(220)),
				static_cast<System::Int32>(static_cast<System::Byte>(47)));
			this->textBox2->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->textBox2->Location = System::Drawing::Point(233, 174);
			this->textBox2->MaxLength = 15;
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(248, 18);
			this->textBox2->TabIndex = 17;
			this->textBox2->UseSystemPasswordChar = true;
			// 
			// panel3
			// 
			this->panel3->BackColor = System::Drawing::SystemColors::ControlText;
			this->panel3->Location = System::Drawing::Point(231, 251);
			this->panel3->Name = L"panel3";
			this->panel3->Size = System::Drawing::Size(249, 1);
			this->panel3->TabIndex = 20;
			// 
			// textBox3
			// 
			this->textBox3->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(220)),
				static_cast<System::Int32>(static_cast<System::Byte>(47)));
			this->textBox3->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->textBox3->Location = System::Drawing::Point(232, 227);
			this->textBox3->MaxLength = 15;
			this->textBox3->Name = L"textBox3";
			this->textBox3->Size = System::Drawing::Size(248, 18);
			this->textBox3->TabIndex = 19;
			this->textBox3->UseSystemPasswordChar = true;
			// 
			// panel4
			// 
			this->panel4->BackColor = System::Drawing::SystemColors::ControlText;
			this->panel4->Location = System::Drawing::Point(231, 302);
			this->panel4->Name = L"panel4";
			this->panel4->Size = System::Drawing::Size(249, 1);
			this->panel4->TabIndex = 22;
			// 
			// textBox4
			// 
			this->textBox4->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(220)),
				static_cast<System::Int32>(static_cast<System::Byte>(47)));
			this->textBox4->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->textBox4->Location = System::Drawing::Point(233, 278);
			this->textBox4->MaxLength = 5;
			this->textBox4->Name = L"textBox4";
			this->textBox4->Size = System::Drawing::Size(248, 18);
			this->textBox4->TabIndex = 21;
			// 
			// panel5
			// 
			this->panel5->BackColor = System::Drawing::SystemColors::ControlText;
			this->panel5->Location = System::Drawing::Point(229, 450);
			this->panel5->Name = L"panel5";
			this->panel5->Size = System::Drawing::Size(249, 1);
			this->panel5->TabIndex = 24;
			// 
			// textBox5
			// 
			this->textBox5->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(220)),
				static_cast<System::Int32>(static_cast<System::Byte>(47)));
			this->textBox5->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->textBox5->Location = System::Drawing::Point(231, 426);
			this->textBox5->MaxLength = 15;
			this->textBox5->Name = L"textBox5";
			this->textBox5->Size = System::Drawing::Size(248, 18);
			this->textBox5->TabIndex = 23;
			// 
			// dateTimePicker1
			// 
			this->dateTimePicker1->Format = System::Windows::Forms::DateTimePickerFormat::Short;
			this->dateTimePicker1->Location = System::Drawing::Point(231, 382);
			this->dateTimePicker1->MaxDate = System::DateTime(2024, 3, 5, 16, 46, 41, 426);
			this->dateTimePicker1->Name = L"dateTimePicker1";
			this->dateTimePicker1->Size = System::Drawing::Size(137, 25);
			this->dateTimePicker1->TabIndex = 25;
			this->dateTimePicker1->Value = System::DateTime(2024, 3, 5, 16, 46, 41, 426);
			this->dateTimePicker1->ValueChanged += gcnew System::EventHandler(this, &newForm::dateTimePicker1_ValueChanged);
			// 
			// button2
			// 
			this->button2->BackColor = System::Drawing::Color::Transparent;
			this->button2->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(129)));
			this->button2->ForeColor = System::Drawing::Color::DarkRed;
			this->button2->Location = System::Drawing::Point(515, 110);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(114, 34);
			this->button2->TabIndex = 26;
			this->button2->Text = L"중복확인";
			this->button2->UseVisualStyleBackColor = false;
			this->button2->Click += gcnew System::EventHandler(this, &newForm::button2_Click);
			// 
			// button3
			// 
			this->button3->BackColor = System::Drawing::Color::Transparent;
			this->button3->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(129)));
			this->button3->ForeColor = System::Drawing::Color::DarkRed;
			this->button3->Location = System::Drawing::Point(515, 216);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(114, 36);
			this->button3->TabIndex = 27;
			this->button3->Text = L"비밀번호확인";
			this->button3->UseVisualStyleBackColor = false;
			this->button3->Click += gcnew System::EventHandler(this, &newForm::button3_Click);
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10));
			this->label8->Location = System::Drawing::Point(125, 338);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(33, 20);
			this->label8->TabIndex = 28;
			this->label8->Text = L"성별";
			// 
			// checkBox2
			// 
			this->checkBox2->AutoCheck = false;
			this->checkBox2->AutoSize = true;
			this->checkBox2->Location = System::Drawing::Point(645, 222);
			this->checkBox2->Name = L"checkBox2";
			this->checkBox2->Size = System::Drawing::Size(18, 17);
			this->checkBox2->TabIndex = 30;
			this->checkBox2->UseVisualStyleBackColor = true;
			// 
			// radioButton1
			// 
			this->radioButton1->AutoSize = true;
			this->radioButton1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(129)));
			this->radioButton1->Location = System::Drawing::Point(230, 334);
			this->radioButton1->Name = L"radioButton1";
			this->radioButton1->Size = System::Drawing::Size(55, 22);
			this->radioButton1->TabIndex = 32;
			this->radioButton1->TabStop = true;
			this->radioButton1->Text = L"남성";
			this->radioButton1->UseVisualStyleBackColor = true;
			this->radioButton1->CheckedChanged += gcnew System::EventHandler(this, &newForm::radioButton1_CheckedChanged);
			// 
			// radioButton2
			// 
			this->radioButton2->AutoSize = true;
			this->radioButton2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(129)));
			this->radioButton2->Location = System::Drawing::Point(368, 334);
			this->radioButton2->Name = L"radioButton2";
			this->radioButton2->Size = System::Drawing::Size(55, 22);
			this->radioButton2->TabIndex = 33;
			this->radioButton2->TabStop = true;
			this->radioButton2->Text = L"여성";
			this->radioButton2->UseVisualStyleBackColor = true;
			this->radioButton2->CheckedChanged += gcnew System::EventHandler(this, &newForm::radioButton2_CheckedChanged);
			// 
			// checkBox3
			// 
			this->checkBox3->AutoCheck = false;
			this->checkBox3->AutoSize = true;
			this->checkBox3->Enabled = false;
			this->checkBox3->Location = System::Drawing::Point(645, 116);
			this->checkBox3->Name = L"checkBox3";
			this->checkBox3->Size = System::Drawing::Size(18, 17);
			this->checkBox3->TabIndex = 34;
			this->checkBox3->UseVisualStyleBackColor = true;
			// 
			// label9
			// 
			this->label9->AutoSize = true;
			this->label9->Location = System::Drawing::Point(381, 389);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(0, 15);
			this->label9->TabIndex = 35;
			// 
			// botton_Exit
			// 
			this->botton_Exit->BackColor = System::Drawing::Color::DarkRed;
			this->botton_Exit->FlatAppearance->BorderSize = 0;
			this->botton_Exit->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->botton_Exit->Font = (gcnew System::Drawing::Font(L"굴림", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(129)));
			this->botton_Exit->ForeColor = System::Drawing::Color::White;
			this->botton_Exit->Location = System::Drawing::Point(689, 16);
			this->botton_Exit->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->botton_Exit->Name = L"botton_Exit";
			this->botton_Exit->Size = System::Drawing::Size(50, 49);
			this->botton_Exit->TabIndex = 36;
			this->botton_Exit->Text = L"X";
			this->botton_Exit->UseVisualStyleBackColor = false;
			this->botton_Exit->Click += gcnew System::EventHandler(this, &newForm::botton_Exit_Click);
			// 
			// label10
			// 
			this->label10->AutoSize = true;
			this->label10->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(129)));
			this->label10->ForeColor = System::Drawing::SystemColors::ControlDarkDark;
			this->label10->Location = System::Drawing::Point(485, 429);
			this->label10->Name = L"label10";
			this->label10->Size = System::Drawing::Size(198, 18);
			this->label10->TabIndex = 37;
			this->label10->Text = L"채팅방에서 사용할 닉네임입니다";
			// 
			// label11
			// 
			this->label11->AutoSize = true;
			this->label11->ForeColor = System::Drawing::Color::Red;
			this->label11->Location = System::Drawing::Point(91, 120);
			this->label11->Name = L"label11";
			this->label11->Size = System::Drawing::Size(14, 15);
			this->label11->TabIndex = 38;
			this->label11->Text = L"*";
			// 
			// label12
			// 
			this->label12->AutoSize = true;
			this->label12->ForeColor = System::Drawing::Color::Red;
			this->label12->Location = System::Drawing::Point(102, 173);
			this->label12->Name = L"label12";
			this->label12->Size = System::Drawing::Size(14, 15);
			this->label12->TabIndex = 39;
			this->label12->Text = L"*";
			// 
			// label13
			// 
			this->label13->AutoSize = true;
			this->label13->ForeColor = System::Drawing::Color::Red;
			this->label13->Location = System::Drawing::Point(91, 227);
			this->label13->Name = L"label13";
			this->label13->Size = System::Drawing::Size(14, 15);
			this->label13->TabIndex = 40;
			this->label13->Text = L"*";
			// 
			// label14
			// 
			this->label14->AutoSize = true;
			this->label14->ForeColor = System::Drawing::Color::Red;
			this->label14->Location = System::Drawing::Point(112, 279);
			this->label14->Name = L"label14";
			this->label14->Size = System::Drawing::Size(14, 15);
			this->label14->TabIndex = 41;
			this->label14->Text = L"*";
			// 
			// label15
			// 
			this->label15->AutoSize = true;
			this->label15->ForeColor = System::Drawing::Color::Red;
			this->label15->Location = System::Drawing::Point(112, 389);
			this->label15->Name = L"label15";
			this->label15->Size = System::Drawing::Size(14, 15);
			this->label15->TabIndex = 42;
			this->label15->Text = L"*";
			// 
			// label16
			// 
			this->label16->AutoSize = true;
			this->label16->ForeColor = System::Drawing::Color::Red;
			this->label16->Location = System::Drawing::Point(102, 436);
			this->label16->Name = L"label16";
			this->label16->Size = System::Drawing::Size(14, 15);
			this->label16->TabIndex = 43;
			this->label16->Text = L"*";
			// 
			// label17
			// 
			this->label17->AutoSize = true;
			this->label17->ForeColor = System::Drawing::Color::Red;
			this->label17->Location = System::Drawing::Point(101, 84);
			this->label17->Name = L"label17";
			this->label17->Size = System::Drawing::Size(14, 15);
			this->label17->TabIndex = 44;
			this->label17->Text = L"*";
			// 
			// label18
			// 
			this->label18->AutoSize = true;
			this->label18->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(129)));
			this->label18->ForeColor = System::Drawing::SystemColors::ControlDarkDark;
			this->label18->Location = System::Drawing::Point(112, 83);
			this->label18->Name = L"label18";
			this->label18->Size = System::Drawing::Size(223, 18);
			this->label18->TabIndex = 45;
			this->label18->Text = L"해당 항목은 필수로 입력해야 합니다.";
			// 
			// label19
			// 
			this->label19->AutoSize = true;
			this->label19->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Underline)),
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(129)));
			this->label19->ForeColor = System::Drawing::SystemColors::ControlDarkDark;
			this->label19->Location = System::Drawing::Point(470, 526);
			this->label19->Name = L"label19";
			this->label19->Size = System::Drawing::Size(60, 18);
			this->label19->TabIndex = 46;
			this->label19->Text = L"규정보기";
			// 
			// newForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 15);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(253)), static_cast<System::Int32>(static_cast<System::Byte>(220)),
				static_cast<System::Int32>(static_cast<System::Byte>(47)));
			this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->ClientSize = System::Drawing::Size(760, 700);
			this->Controls->Add(this->label19);
			this->Controls->Add(this->label18);
			this->Controls->Add(this->label17);
			this->Controls->Add(this->label16);
			this->Controls->Add(this->label15);
			this->Controls->Add(this->label14);
			this->Controls->Add(this->label13);
			this->Controls->Add(this->label12);
			this->Controls->Add(this->label11);
			this->Controls->Add(this->label10);
			this->Controls->Add(this->botton_Exit);
			this->Controls->Add(this->label9);
			this->Controls->Add(this->checkBox3);
			this->Controls->Add(this->radioButton2);
			this->Controls->Add(this->radioButton1);
			this->Controls->Add(this->checkBox2);
			this->Controls->Add(this->label8);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->dateTimePicker1);
			this->Controls->Add(this->panel5);
			this->Controls->Add(this->textBox5);
			this->Controls->Add(this->panel4);
			this->Controls->Add(this->textBox4);
			this->Controls->Add(this->panel3);
			this->Controls->Add(this->textBox3);
			this->Controls->Add(this->panel2);
			this->Controls->Add(this->textBox2);
			this->Controls->Add(this->panel1);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->label7);
			this->Controls->Add(this->label6);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->checkBox1);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->label1);
			this->Cursor = System::Windows::Forms::Cursors::Hand;
			this->Font = (gcnew System::Drawing::Font(L"굴림", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(129)));
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			this->Margin = System::Windows::Forms::Padding(3, 4, 3, 4);
			this->Name = L"newForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"newForm";
			this->Load += gcnew System::EventHandler(this, &newForm::newForm_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void checkBox1_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {

		if (checkBox1->Checked) {
			button1->Enabled = true; // 아이디 중복 체크박스가 체크 되어있으면 버튼1 사용가능         
		}
		else {
			button1->Enabled = false;  //그렇지 않으면 버튼 비활성화
		}
	}
	private: System::Void newForm_Load(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {  // 회원가입 버튼 클릭시
		if (String::IsNullOrEmpty(textBox1->Text))  // ID 빈칸일때
		{
			MessageBox::Show("아이디를 입력하세요.", "info", MessageBoxButtons::OK, MessageBoxIcon::Warning);
		}
		else if (checkBox3->Checked == false) {  // 아이디 중복 확인을 안했을 때
			MessageBox::Show("아이디 중복확인을 하세요.", "info", MessageBoxButtons::OK, MessageBoxIcon::Error);
		}
		else if (String::IsNullOrEmpty(textBox2->Text))  // PW 빈칸일 때
		{
			MessageBox::Show("비밀번호를 입력하세요.", "info", MessageBoxButtons::OK, MessageBoxIcon::Warning);
		}
		else if (checkBox2->Checked == false) {  // 비밀번호 일치 확인을 안했을 때
			MessageBox::Show("비밀번호 일치확인을 하세요.", "info", MessageBoxButtons::OK, MessageBoxIcon::Error);
		}
		else if (String::IsNullOrEmpty(textBox4->Text))  // name 빈칸일 때 
		{
			MessageBox::Show("이름을 입력하세요.", "info", MessageBoxButtons::OK, MessageBoxIcon::Warning);
		}
		else if (String::IsNullOrEmpty(label9->Text))  //생일을 설정하지 않았을 때
		{
			MessageBox::Show("생일을 선택하세요.", "info", MessageBoxButtons::OK, MessageBoxIcon::Warning);
		}
		else if (String::IsNullOrEmpty(textBox5->Text))  //닉네임 빈칸일 때
		{
			MessageBox::Show("닉네임을 입력하세요.", "info", MessageBoxButtons::OK, MessageBoxIcon::Warning);
		}
		else {   // 제대로 입력이 끝났을때 
			//각각의 정보 저장 
			//성별 저장


			Application::Exit();    // 창 닫기-> 채팅방 입장
		}
	}
	private: System::Void button3_Click(System::Object^ sender, System::EventArgs^ e) {
		if (String::IsNullOrEmpty(textBox1->Text) || String::IsNullOrEmpty(textBox2->Text)) {
			MessageBox::Show("비밀번호를 입력하세요.", "Info", MessageBoxButtons::OK, MessageBoxIcon::Warning);
			checkBox2->Checked = false;
		}
		else if (textBox2->Text == textBox3->Text) {
			MessageBox::Show("비밀번호가 일치합니다.", "Info", MessageBoxButtons::OK, MessageBoxIcon::Information);
			checkBox2->Checked = true;
		}
		else {
			MessageBox::Show("비밀번호가 일치하지 않습니다.", "Info", MessageBoxButtons::OK, MessageBoxIcon::Warning);
			checkBox2->Checked = false;
		}
	}

	private: System::Void radioButton1_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {  // 남성 선택
		gender = "M";
	}
	private: System::Void radioButton2_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {  // 여성 선택 
		gender = "F";
	}

	private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) { // 아이디 중복확인 버튼
		if (String::IsNullOrEmpty(textBox1->Text)) {
			MessageBox::Show("아이디를 입력하세요.", "Info", MessageBoxButtons::OK, MessageBoxIcon::Warning);
			checkBox3->Checked = false;
		}
		else {
			String^ id = textBox1->Text->Replace("", " ");
			_clnt->SendMessage(id);
		}
	}

	private: System::Void dateTimePicker1_ValueChanged(System::Object^ sender, System::EventArgs^ e) {

		label9->Text = dateTimePicker1->Value.ToShortDateString();
	}
	private: System::Void botton_Exit_Click(System::Object^ sender, System::EventArgs^ e) {
		this->Close();

	}
		   //public: void chatroomShow() {
		   //	if (chatform == nullptr || chatform->IsDisposed) {
		   //		chatform = gcnew chatroom(_clnt);
		   //		chatform->Owner = this; // Owner를 설정해야 가능
		   //		this->Hide();
		   //		//this->HomeImageSound->Stop();
		   //		chatform->Show();
		   //	}
		   //	return;
		   //}
	public: void ReceivedMsg(String^ message)
	{
		String^ inputString = message;

		array<String^>^ subString = inputString->Split(' ');

		//String^ index_s = subString[0];
		String^ isTrue = subString[1];
		//int index = Int32::Parse(index_s);


		//if (isTrue == "true")
		//{
		//this->Invoke(gcnew MethodInvoker(this, &MyForm::chatroomShow));
		//System::Windows::Forms::MessageBox::Show("성공!!", "warning", MessageBoxButtons::OK, MessageBoxIcon::Warning);

		//else
		//{
		//	System::Windows::Forms::MessageBox::Show("Check the ID and Password", "warning", MessageBoxButtons::OK, MessageBoxIcon::Warning);
		//}

	}

	private: System::Void textBox1_TextChanged(System::Object^ sender, System::EventArgs^ e) {
	}
};
}
