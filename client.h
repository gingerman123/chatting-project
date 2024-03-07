#pragma once
#pragma comment(lib, "ws2_32.lib")

#include <WinSock2.h> //Winsock ������� include. WSADATA �������.
#include <WS2tcpip.h>

namespace Socket_cli {

	using namespace System;
	using namespace System::Net;
	using namespace System::Net::Sockets;
	using namespace System::Windows::Forms;
	using namespace System::Text;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::ComponentModel;
	using namespace System::Collections;

	ref class client
	{
	public:
		IPEndPoint^ serverEndPoint;
		Socket^ clientSocket;
		System::Threading::Thread^ messageReceiveThread;

		// �̺�Ʈ�� �����մϴ�.
		event Action<String^>^ MyEvent;


	public:
		void SendMessage(String^ message)
		{

			if (!String::IsNullOrEmpty(message))
			{
				//array<Byte>^ buffer = Encoding::UTF8->GetBytes(message);
				cli::array<Byte>^ buffer = System::Text::Encoding::GetEncoding("EUC-KR")->GetBytes(message);
				clientSocket->Send(buffer, buffer->Length, SocketFlags::None);

			}
		}
		void ReceiveMessages()
		{
			
			while (true)
			{
				try
				{
					cli::array<Byte>^ buffer = gcnew cli::array<Byte>(1024);
					int bytesRead = clientSocket->Receive(buffer);
					//String^ message = System::Text::Encoding::UTF8->GetString(buffer, 0, bytesRead);	//�ѱ� �ȵ�, ���
					//String^ message = System::Text::Encoding::GetEncoding("EUC-KR")->GetString(buffer, 0, buffer->Length);	//�ѱ� �Ǵ³�
					String^ message = System::Text::Encoding::GetEncoding("EUC-KR")->GetString(buffer, 0, bytesRead);	//�ѱ� �Ǵ³�
					/*array<String^>^ subString = message->Split(' ');*/
					/*String^ msg = subString[0];*/

					if (!String::IsNullOrEmpty(message))
					{
						Console::WriteLine("Sent message: " + message);
						MyEvent(message);
						
					}

					//AppendMessageToUI("����: " + message);
				}
				catch (SocketException^ se)
				{
					// �������� ������ ������ �� SocketException�� ó���մϴ�.
					// ���� ó�� �ڵ� �߰�, ���� ���:
					// 
					MessageBox::Show("Server disconnected");
					break; // ������ ���� �Ǵ� �ٸ� ��ġ�� ���� �� ����
				}
			}
		}
		void init_client() {
			System::Threading::Thread^ messageReceiveThread = nullptr;

			WSADATA wsaData;
			if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
				MessageBox::Show("���� �ʱ�ȭ�� �����߽��ϴ�.");
				Application::Exit();
			}

			// ���� ����
			clientSocket = gcnew Socket(AddressFamily::InterNetwork, SocketType::Stream, ProtocolType::Tcp);

			// ���� �ּ� ����
			serverEndPoint = gcnew IPEndPoint(IPAddress::Parse("127.0.0.1"), 7777);	//
		}
		void Connect() {
			while (1) {
				try {
					clientSocket->Connect(serverEndPoint);
					// ���� ������ �����带 �����Ͽ� �޽��� ���� ���
					messageReceiveThread = gcnew System::Threading::Thread(gcnew System::Threading::ThreadStart(this, &client::ReceiveMessages));
					messageReceiveThread->Start();
					break;

				}		
				catch (Exception^ e) {
					MessageBox::Show("server connection failed", "error" + e->Message);
				}
				Sleep(3000);
			}
		}
		void disposed()
		{
			// ���� ����
			clientSocket->Close();
			if (messageReceiveThread != nullptr)
			{
				messageReceiveThread->Abort();
			}
		}
	};
}