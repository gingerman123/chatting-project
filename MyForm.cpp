#include "MyForm.h"
#include "client.h"

using namespace System;
using namespace System::Windows::Forms;
using namespace Project1;
using namespace Socket_cli;


[STAThreadAttribute]


int main(cli::array<String^>^ args) {



	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	Socket_cli::client form;
	form.init_client();
	form.Connect();
	MyForm my(% form);
	Application::Run(% my);

	form.disposed();

	return 0;
}
