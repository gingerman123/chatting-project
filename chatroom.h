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
	/// chatroom에 대한 요약입니다.
	/// </summary>
	public ref class chatroom : public System::Windows::Forms::Form
	{


	public:
		chatroom(void)
		{
			InitializeComponent();
			//
			//TODO: 생성자 코드를 여기에 추가합니다.
			//
		}
		chatroom(client^ clnt) {

			InitializeComponent();
			_clnt = clnt;
			_clnt->MyEvent += gcnew Action<String^>(this, &chatroom::ReceivedMsg);
			this->AcceptButton = button1; //엔터키?
		}

	protected:
		/// <summary>
		/// 사용 중인 모든 리소스를 정리합니다.
		/// </summary>
		~chatroom()
		{
			if (components)
			{
				delete components;
			}
		}
	private: client^ _clnt;
	private: System::Windows::Forms::Button^ button1;

	private: System::Windows::Forms::RichTextBox^ richTextBox1;
	private: System::Windows::Forms::Button^ botton_Exit;

	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::RichTextBox^ richTextBox2;


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
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->richTextBox1 = (gcnew System::Windows::Forms::RichTextBox());
			this->botton_Exit = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->richTextBox2 = (gcnew System::Windows::Forms::RichTextBox());
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(128)), static_cast<System::Int32>(static_cast<System::Byte>(64)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)));
			this->button1->FlatAppearance->BorderColor = System::Drawing::Color::Maroon;
			this->button1->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button1->Font = (gcnew System::Drawing::Font(L"Cafe24 Ssurround air OTF Light", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(129)));
			this->button1->ForeColor = System::Drawing::SystemColors::ControlLightLight;
			this->button1->Location = System::Drawing::Point(684, 551);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(132, 76);
			this->button1->TabIndex = 0;
			this->button1->Text = L"전송";
			this->button1->UseVisualStyleBackColor = false;
			this->button1->Click += gcnew System::EventHandler(this, &chatroom::button1_Click);
			// 
			// richTextBox1
			// 
			this->richTextBox1->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->richTextBox1->Font = (gcnew System::Drawing::Font(L"맑은 고딕", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->richTextBox1->Location = System::Drawing::Point(33, 551);
			this->richTextBox1->MaxLength = 30;
			this->richTextBox1->Name = L"richTextBox1";
			this->richTextBox1->Size = System::Drawing::Size(608, 76);
			this->richTextBox1->TabIndex = 0;
			this->richTextBox1->Text = L"";
			this->richTextBox1->TextChanged += gcnew System::EventHandler(this, &chatroom::richTextBox1_TextChanged);
			// 
			// botton_Exit
			// 
			this->botton_Exit->BackColor = System::Drawing::Color::Transparent;
			this->botton_Exit->FlatAppearance->BorderSize = 2;
			this->botton_Exit->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->botton_Exit->Font = (gcnew System::Drawing::Font(L"Cafe24 Ssurround air OTF Light", 10.8F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(129)));
			this->botton_Exit->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(128)), static_cast<System::Int32>(static_cast<System::Byte>(64)),
				static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->botton_Exit->Location = System::Drawing::Point(697, 64);
			this->botton_Exit->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->botton_Exit->Name = L"botton_Exit";
			this->botton_Exit->Size = System::Drawing::Size(119, 72);
			this->botton_Exit->TabIndex = 10;
			this->botton_Exit->Text = L"채팅방\r\n나가기";
			this->botton_Exit->UseVisualStyleBackColor = false;
			this->botton_Exit->Click += gcnew System::EventHandler(this, &chatroom::botton_Exit_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Cafe24 Ssurround OTF Bold", 24, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(129)));
			this->label1->Location = System::Drawing::Point(331, 9);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(136, 52);
			this->label1->TabIndex = 11;
			this->label1->Text = L"채팅방";
			// 
			// richTextBox2
			// 
			this->richTextBox2->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(255)),
				static_cast<System::Int32>(static_cast<System::Byte>(192)));
			this->richTextBox2->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->richTextBox2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(129)));
			this->richTextBox2->Location = System::Drawing::Point(33, 64);
			this->richTextBox2->Name = L"richTextBox2";
			this->richTextBox2->ReadOnly = true;
			this->richTextBox2->Size = System::Drawing::Size(608, 470);
			this->richTextBox2->TabIndex = 12;
			this->richTextBox2->Text = L"";
			this->richTextBox2->TextChanged += gcnew System::EventHandler(this, &chatroom::richTextBox2_TextChanged);
			// 
			// chatroom
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(10, 20);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(233)),
				static_cast<System::Int32>(static_cast<System::Byte>(151)));
			this->ClientSize = System::Drawing::Size(851, 653);
			this->Controls->Add(this->richTextBox2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->botton_Exit);
			this->Controls->Add(this->richTextBox1);
			this->Controls->Add(this->button1);
			this->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(129)));
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			this->Margin = System::Windows::Forms::Padding(4);
			this->Name = L"chatroom";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"chatroom";
			this->Load += gcnew System::EventHandler(this, &chatroom::chatroom_Load);
			this->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &chatroom::chatroom_MouseDown);
			this->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &chatroom::chatroom_MouseMove);
			this->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &chatroom::chatroom_MouseUp);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
	private:
		void richTextBox1_KeyDown(Object^ sender, KeyEventArgs^ e) {
			// RichTextBox의 KeyDown 이벤트 핸들러 추가
			richTextBox1->KeyDown += gcnew KeyEventHandler(this, &chatroom::richTextBox1_KeyDown);
			if (e->KeyCode == Keys::Enter) {
				// 엔터 키를 누르면 특정 버튼 클릭 또는 원하는 동작 수행
				button1->PerformClick();
				// 또는 다른 작업 수행
			}
		}

#pragma endregion
		bool dragging;
		Point offset;
	private: System::Void chatroom_Load(System::Object^ sender, System::EventArgs^ e) {
		richTextBox2->Text = "";
	}
	private: System::Void chatroom_MouseMove(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
		if (dragging) {
			Point currentScreenPosiotion = PointToScreen(Point(e->X, e->Y));
			Location = Point(currentScreenPosiotion.X - offset.X, currentScreenPosiotion.Y - offset.Y);
		}
	}
	private: System::Void chatroom_MouseUp(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
		dragging = false;
	}
	private: System::Void chatroom_MouseDown(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
		dragging = true;
		offset.X = e->X;
		offset.Y = e->Y;
	}
	private: System::Void botton_Exit_Click(System::Object^ sender, System::EventArgs^ e) {

		if (MessageBox::Show("정말로 종료하시겠습니까?", "Exit?", MessageBoxButtons::YesNo, MessageBoxIcon::Warning) == System::Windows::Forms::DialogResult::Yes)
			Application::Exit();
	}

	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {

		//String^ me = "[나] : ";

		// 오른쪽 정렬을 위해 현재 위치를 저장하고, 새로운 줄을 추가합니다.
		//int currentPosition = richTextBox2->SelectionStart;
		//richTextBox2->Text += me + richTextBox1->Text + "\n";

		//// 텍스트를 오른쪽 정렬로 설정하고, 현재 위치를 복원합니다.  
		//richTextBox2->SelectionStart = currentPosition;
		//richTextBox2->SelectionLength = me->Length + richTextBox1->Text->Length;
		//richTextBox2->SelectionAlignment = HorizontalAlignment::Right;
		//richTextBox2->SelectionStart = richTextBox2->Text->Length;
		String^ message = "msg" + " " + richTextBox1->Text;
		_clnt->SendMessage(message);
		richTextBox1->Text = "";

	}
	private: System::Void richTextBox1_TextChanged(System::Object^ sender, System::EventArgs^ e) {
		if (richTextBox1->Text->EndsWith(Environment::NewLine)) {
			// Enter 키를 눌렀을 때 수행할 작업을 여기에 추가
			button1_Click(sender, e);
			richTextBox1->Text = richTextBox1->Text->TrimEnd(Environment::NewLine->ToCharArray()); //줄바꿈방지:새 줄 제거
		}
	}

	public: void ReceivedMsg(String^ message)
	{
		String^ inputString = message;
		int index = inputString->IndexOf('%');
		String^ ident;
		String^ what;
		if (index != -1) { // "%"가 발견된 경우에만 처리
			ident = inputString->Substring(0, index);
			what = inputString->Substring(index + 1); // 첫 번째 "%" 이후의 문자열
		}
		String^ any = "msg";
		String^ any1 = "cur";

		richTextBox2->Text += what + "\n";
		richTextBox2->SelectionStart = richTextBox2->Text->Length;
		richTextBox2->ScrollToCaret();
		

	}
	private: System::Void richTextBox2_TextChanged(System::Object^ sender, System::EventArgs^ e) {
	}
};
}





