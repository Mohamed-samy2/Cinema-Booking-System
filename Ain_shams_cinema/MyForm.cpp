#include "MyForm.h"
using namespace System;
using namespace System::Windows::Forms;
[STAThread]

void main(cli::array<String^>^ args) {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	Ainshamscinema::MyForm form;
	Application::Run(% form);

}

/*void SendMail(String^ sender,
    String^ toRecipients,
    String^ ccRecipients,
    String^ subject,
    String^ bodyText,
    String^ server,
    String^ user,
    String^ password,
    bool useSsl)
{
    try
    {
        // From is a MailAddress object, it also supports implicit converting from string. 
        // The syntax is like this: "test@adminsystem.com" or "Tester <test@adminsystem.com>"

        // oMail->From = gcnew MailAddress("Tester", "test@adminsystem.com"); 
        // oMail->From = gcnew MailAddress("Tester <test@adminsystem.com>"); 
        // oMail->From = gcnew MailAddress("test@adminsystem.com"); 

        //To, Cc and Bcc is a AddressCollection object, it also supports implicit converting from string.
        // multiple address should be separated with (,;) 
        //The syntax is like this: "test@adminsystem.com, test1@adminsystem.com" 

        // oMail->To  = gcnew AddressCollection("test1@adminsystem.com, test2@adminsystem.com"); 
        // oMail->To = gcnew AddressCollection("Tester1 <test@adminsystem.com>, Tester2 <test2@adminsystem.com>");

        // You can add more recipient by Add method 
        // oMail->To->Add(gcnew MailAddress("tester", "test@adminsystem.com")); 

        SmtpMail^ oMail = gcnew SmtpMail("TryIt");

        oMail->From = gcnew EASendMail::MailAddress(sender);
        oMail->To = gcnew EASendMail::AddressCollection(toRecipients);
        oMail->Cc = gcnew EASendMail::AddressCollection(ccRecipients);

        oMail->Subject = subject;

        // If bodyText contains html tags, please use 
        // oMail->HtmlBody = bodyText; 
        oMail->TextBody = bodyText;

        // Add attachment 
        // oMail->AddAttachment("c:\\test.gif");      

        // Set server address
        SmtpServer^ oServer = gcnew SmtpServer(server);
        if (user->Length != 0 && password->Length != 0)
        {
            // Set user/password for ESMTP authentication
            oServer->User = user;
            oServer->Password = password;
        }

        // Most mordern SMTP servers require SSL/TLS connection now.
        // ConnectTryTLS means if server supports SSL/TLS, SSL/TLS will be used automatically.
        oServer->ConnectType = (useSsl) ? SmtpConnectType::ConnectSSLAuto : SmtpConnectType::ConnectTryTLS;

        SmtpClient^ oSmtp = gcnew SmtpClient();

        // To generate a log file for SMTP transaction, please use 
        // oSmtp->LogFileName = "c:\\smtp.txt";

        oSmtp->SendMail(oServer, oMail);

             //Console::WriteLine("The message has been submitted to server successfully!");
    }
    catch (Exception^ exp)
    {
        //Console::WriteLine("Exception: {0}", exp->Message);
    }
 }*/

