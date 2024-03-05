#pragma once
#include "client.h"

namespace Project1 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace Socket_cli;

	/// <summary>
	/// FindPW에 대한 요약입니다.
	/// </summary>
	public ref class FindPW : public System::Windows::Forms::Form
	{
	public:
		FindPW(void)
		{
			InitializeComponent();
			//
			//TODO: 생성자 코드를 여기에 추가합니다.
			//
		}

		FindPW(client^ my)
		{
			InitializeComponent();
			//
			//TODO: 생성자 코드를 여기에 추가합니다.
			//
			_my = my;
			_my->MyEvent += gcnew Action<String^>(this, &FindPW::ReceivedMsg);

		}
	private: client^ _my;

	protected:
		/// <summary>
		/// 사용 중인 모든 리소스를 정리합니다.
		/// </summary>
		~FindPW()
		{
			if (_my != nullptr) {
				// MyEvent 이벤트 핸들러를 해제
				_my->MyEvent -= gcnew Action<String^>(this, &FindPW::ReceivedMsg);

				// _my를 삭제
				delete _my;
				_my = nullptr;  // nullptr로 설정하여 dangling pointer를 방지
			}
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^ botton_Exit;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::Panel^ panel1;
	private: System::Windows::Forms::TextBox^ textBox1;
	private: System::Windows::Forms::DateTimePicker^ dateTimePicker1;



	protected:

	protected:

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
			this->botton_Exit = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->dateTimePicker1 = (gcnew System::Windows::Forms::DateTimePicker());
			this->SuspendLayout();
			// 
			// botton_Exit
			// 
			this->botton_Exit->BackColor = System::Drawing::Color::Transparent;
			this->botton_Exit->FlatAppearance->BorderSize = 2;
			this->botton_Exit->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->botton_Exit->Font = (gcnew System::Drawing::Font(L"굴림", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(129)));
			this->botton_Exit->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(128)), static_cast<System::Int32>(static_cast<System::Byte>(64)),
				static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->botton_Exit->Location = System::Drawing::Point(634, 25);
			this->botton_Exit->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->botton_Exit->Name = L"botton_Exit";
			this->botton_Exit->Size = System::Drawing::Size(45, 41);
			this->botton_Exit->TabIndex = 10;
			this->botton_Exit->Text = L"X";
			this->botton_Exit->UseVisualStyleBackColor = false;
			this->botton_Exit->Click += gcnew System::EventHandler(this, &FindPW::botton_Exit_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->BackColor = System::Drawing::Color::Transparent;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 13.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(129)));
			this->label1->Location = System::Drawing::Point(289, 25);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(145, 29);
			this->label1->TabIndex = 11;
			this->label1->Text = L"비밀번호 찾기";
			this->label1->Click += gcnew System::EventHandler(this, &FindPW::label1_Click);
			// 
			// button1
			// 
			this->button1->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(255)),
				static_cast<System::Int32>(static_cast<System::Byte>(192)));
			this->button1->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(192)),
				static_cast<System::Int32>(static_cast<System::Byte>(192)), static_cast<System::Int32>(static_cast<System::Byte>(0)));
			this->button1->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(129)));
			this->button1->ForeColor = System::Drawing::SystemColors::ControlText;
			this->button1->Location = System::Drawing::Point(435, 188);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(115, 90);
			this->button1->TabIndex = 16;
			this->button1->Text = L"찾기";
			this->button1->UseVisualStyleBackColor = false;
			this->button1->Click += gcnew System::EventHandler(this, &FindPW::button1_Click);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->BackColor = System::Drawing::Color::Transparent;
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(129)));
			this->label2->Location = System::Drawing::Point(116, 234);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(72, 25);
			this->label2->TabIndex = 18;
			this->label2->Text = L"생년월일";
			this->label2->Click += gcnew System::EventHandler(this, &FindPW::label2_Click);
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->BackColor = System::Drawing::Color::Transparent;
			this->label3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(129)));
			this->label3->Location = System::Drawing::Point(116, 154);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(31, 25);
			this->label3->TabIndex = 17;
			this->label3->Text = L"ID";
			this->label3->Click += gcnew System::EventHandler(this, &FindPW::label3_Click);
			// 
			// panel1
			// 
			this->panel1->BackColor = System::Drawing::SystemColors::ControlText;
			this->panel1->Location = System::Drawing::Point(123, 216);
			this->panel1->Margin = System::Windows::Forms::Padding(3, 4, 3, 4);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(180, 1);
			this->panel1->TabIndex = 20;
			// 
			// textBox1
			// 
			this->textBox1->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(234)),
				static_cast<System::Int32>(static_cast<System::Byte>(151)));
			this->textBox1->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->textBox1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(129)));
			this->textBox1->Location = System::Drawing::Point(120, 188);
			this->textBox1->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(183, 21);
			this->textBox1->TabIndex = 19;
			// 
			// dateTimePicker1
			// 
			this->dateTimePicker1->Format = System::Windows::Forms::DateTimePickerFormat::Short;
			this->dateTimePicker1->Location = System::Drawing::Point(120, 286);
			this->dateTimePicker1->Name = L"dateTimePicker1";
			this->dateTimePicker1->Size = System::Drawing::Size(183, 24);
			this->dateTimePicker1->TabIndex = 21;
			// 
			// FindPW
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(9, 18);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(233)),
				static_cast<System::Int32>(static_cast<System::Byte>(151)));
			this->ClientSize = System::Drawing::Size(700, 500);
			this->Controls->Add(this->dateTimePicker1);
			this->Controls->Add(this->panel1);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->botton_Exit);
			this->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(129)));
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			this->Name = L"FindPW";
			this->Text = L"FindPW";
			this->Load += gcnew System::EventHandler(this, &FindPW::FindPW_Load);
			this->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &FindPW::FindPW_MouseDown);
			this->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &FindPW::FindPW_MouseMove);
			this->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &FindPW::FindPW_MouseUp);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void botton_Exit_Click(System::Object^ sender, System::EventArgs^ e) {

		this->Close();
	}
	private: System::Void label1_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void label3_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void label2_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void pictureBox1_Click(System::Object^ sender, System::EventArgs^ e) {
	}

	public: void ReceivedMsg(String^ message)
	{
		String^ inputString = message;

		array<String^>^ subString = inputString->Split(' ');

		String^ call = subString[0];
		String^ pw = subString[1];


		if (call == "Ypw"){
			System::Windows::Forms::MessageBox::Show("비밀번호는 " + pw +"입니다", "비밀번호 알림", MessageBoxButtons::OK, MessageBoxIcon::Information);
		}
		else if (call == "Npw")
		{
			System::Windows::Forms::MessageBox::Show("해당 ID,생일이 없습니다.", "warning", MessageBoxButtons::OK, MessageBoxIcon::Warning);
		}

		
	}
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
		button1->NotifyDefault(false);
		SendMessageForm();
	}



	public: void SendMessageForm()
	{
		String^ id = textBox1->Text->Replace(" ", ""); // textBox는 해당 텍스트 상자의 이름입니다.
		String^ birth = dateTimePicker1->Value.Date.ToString(); // textBox는 해당 텍스트 상자의 이름입니다.
		String^ buffer = "findPW " + id + " " + birth;
		_my->SendMessage(buffer);
	}
private: System::Void FindPW_Load(System::Object^ sender, System::EventArgs^ e) {
}
	bool dragging;
	Point offset;
private: System::Void FindPW_MouseDown(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
	dragging = true;
	offset.X = e->X;
	offset.Y = e->Y;
}
private: System::Void FindPW_MouseUp(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
	dragging = false;

}
private: System::Void FindPW_MouseMove(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
	if (dragging) {
		Point currentScreenPosiotion = PointToScreen(Point(e->X, e->Y));
		Location = Point(currentScreenPosiotion.X - offset.X, currentScreenPosiotion.Y - offset.Y);
	}
}
};



}
