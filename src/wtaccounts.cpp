/*
 * wtaccounts.cpp
 *
 *  Created on: Jul 22, 2016
 *      Author: bigbang
 */

#include <string>
#include <set>
#include <mysql.h>
#include <mysql++.h>
#include <boost/lexical_cast.hpp>
#include <boost/date_time/local_time/local_time.hpp>
#include "wtaccounts.h"

//herdre
#include <iostream>
#include <map>
int dor=0;

/* rand example: guess the number */
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */


WtAccounts::WtAccounts(const Wt::WEnvironment& env) : Wt::WApplication(env), ui(new Ui_WtAccounts)
{
	ui->setupUi(root());
	//ui->menuitem_mi->clicked().connect(boost::bind(&WtAccounts::data_load_user_account_tab, this));
	//ui->user_group_button->clicked().connect(boost::bind(&WtAccounts::subscriber_group_dialog, this));
	//ui->user_full_name_button->clicked().connect(boost::bind(&WtAccounts::subscriber_name_dialog, this));
	//ui->tariff_plan_button->clicked().connect(boost::bind(&WtAccounts::subscriber_tariff_plan_dialog, this));
	//ui->ip_login_button->clicked().connect(boost::bind(&WtAccounts::subscriber_ip_address_dialog, this));
	//ui->menuitem_cp_mi->clicked().connect(boost::bind(&WtAccounts::create_ip_address_dialog, this));
	//ui->user_number_button->clicked().connect(boost::bind(&WtAccounts::subscriber_phone_number_dialog, this));
	//ui->nv_menu_item2_mi->clicked().connect(boost::bind(&WtAccounts::edit_subscriber_load_data, this)); // ***
	//ui->save_close_button->clicked().connect(boost::bind(&WtAccounts::create_user_tab_save_data, this));
	// ui->main_tabs->setCurrentIndex(0);
	//WtAccounts::data_load_user_account_tab();
	// WtAccounts::subscriber_show_operation_tab("view");


	 ui->welcome_user_tab_mi->setHidden(false);
	 ui->main_tabs->setCurrentIndex(4);

	// new regrouping functions
	//ui->nv_menu_item1_mi->clicked().connect(boost::bind(&WtAccounts::subscriber_show_operation_tab, this, "create"));
	//ui->nv_menu_item2_mi->clicked().connect(boost::bind(&WtAccounts::subscriber_show_operation_tab, this, "edit"));
	ui->user_full_name_button->clicked().connect(boost::bind(&WtAccounts::subscriber_name_dialog, this, "create"));
	ui->user_full_name_button_edit_user_tab->clicked().connect(boost::bind(&WtAccounts::subscriber_name_dialog, this, "edit"));
	ui->user_group_button->clicked().connect(boost::bind(&WtAccounts::subscriber_group_dialog, this, "create"));
	ui->user_group_button_edit_user_tab->clicked().connect(boost::bind(&WtAccounts::subscriber_group_dialog, this, "edit"));
	ui->user_number_button->clicked().connect(boost::bind(&WtAccounts::subscriber_phone_number_dialog, this, "create"));
	ui->user_number_button_edit_user_tab->clicked().connect(boost::bind(&WtAccounts::subscriber_phone_number_dialog, this, "edit"));
	ui->ip_login_button->clicked().connect(boost::bind(&WtAccounts::subscriber_ip_address_dialog, this, "create"));
	ui->ip_login_button_edit_user_tab->clicked().connect(boost::bind(&WtAccounts::subscriber_ip_address_dialog, this, "edit"));
	ui->tariff_plan_button->clicked().connect(boost::bind(&WtAccounts::subscriber_tariff_plan_dialog, this, "create"));
	ui->tariff_plan_button_edit_user_tab->clicked().connect(boost::bind(&WtAccounts::subscriber_tariff_plan_dialog, this, "edit"));
	ui->user_address_button->clicked().connect(boost::bind(&WtAccounts::subscriber_contact_dialog, this, "create"));
	ui->user_address_button_edit_user_tab->clicked().connect(boost::bind(&WtAccounts::subscriber_contact_dialog, this, "edit"));
	ui->save_close_button->clicked().connect(boost::bind(&WtAccounts::save_data_and_close_tab, this, "create"));
	ui->save_close_button_edit_user_tab->clicked().connect(boost::bind(&WtAccounts::save_data_and_close_tab, this, "edit"));
	ui->service_button->clicked().connect(boost::bind(&WtAccounts::subscriber_service_dialog, this, "create"));
	ui->service_button_edit_user_tab->clicked().connect(boost::bind(&WtAccounts::subscriber_service_dialog, this, "edit"));
	ui->user_treeTable->tree()->itemSelectionChanged().connect(boost::bind(&WtAccounts::subscriber_fullName_changed, this));

	ui->p_account_operation_split_button_popup->itemSelected().connect(boost::bind(&WtAccounts::account_operation_popup_item_binder, this));

	ui->nv_pp_item1->clicked().connect(boost::bind(&WtAccounts::subscriber_show_operation_tab, this, "view"));
	ui->nv_pp_item2->clicked().connect(boost::bind(&WtAccounts::subscriber_show_operation_tab, this, "create"));
	ui->nv_pp_item3->clicked().connect(boost::bind(&WtAccounts::subscriber_show_operation_tab, this, "edit"));
	ui->nv_pp_item4->clicked().connect(boost::bind(&WtAccounts::manage_services_dialog, this));
	ui->nv_pp_item5->clicked().connect(boost::bind(&WtAccounts::manage_new_call_tariff_dialog, this));

	// herdre functions
    ui->refresh_button->clicked().connect(boost::bind(&WtAccounts::subscriber_fullName_changed, this));
    //Drop out M (Ama data,Netflow data)(make and configure report)
   // ui->p_account_operation_split_button_popup->itemSelected().connect(boost::bind(&WtAccounts::p_account_operation_CHECK, this, "PopUp"));

    //Search
    //ui->user_search_edit->changed().connect(boost::bind(&WtAccounts::search_subscribers, this, "Search"));
    ui->user_search_button->clicked().connect(boost::bind(&WtAccounts::search_subscribers, this, "Search"));
    //Save and close configure of Report
    ui->save_close_button_report_edit->clicked().connect(boost::bind(&WtAccounts::Configure_edited_report_data_Report, this, "save"));

    //fast creat report
    ui->new_report_button->clicked().connect(boost::bind(&WtAccounts::p_account_operation_create_Report, this, "fast",""));
   //send mail to users


    //if tabs closed
    ui->main_tabs->tabClosed().connect(this,&WtAccounts::checkIndex_TAB_close);
    //ui->main_tabs->tabClosed(1).connect(boost::bind(&WtAccounts::checkIndex_close, this));

    //if we switch month with fast button forfard and back
    ui->previous_button->clicked().connect(boost::bind(&WtAccounts::month_button_fastswitch, this, 2));
	ui->next_button->clicked().connect(boost::bind(&WtAccounts::month_button_fastswitch, this, 1));

    //ui->refresh_button->clicked()
	// search when you change text in edit for now it's comment because may slow program
	// ui->user_search_edit->changed().connect(boost::bind(&WtAccounts::search_subscribers, this, "search"));
   // ui->main_tabs->;
	//ui->main_tabs->
}

WtAccounts::~WtAccounts()
{
	delete ui;
}


// mysql variables for connection, store result
MYSQL *conn, mysql;
MYSQL_RES *res;
MYSQL_ROW row;
MYSQL_RES *add_res;
MYSQL_ROW add_row;

//mysq variables for mail
MYSQL_RES *res_mail;
MYSQL_ROW row_mail;

// mysql connections settings
const char *server="52.8.83.48";
const char *user="007";
const char *password="Yeshimbetov^Karakalpak8";
const char *database="account_database";
int query_state;
std::string mysql_query_str = "";


///FOR mail
static const int CHARS= 76;     //Sending 54 chararcters at a time with \r , \n and \0 it becomes 57
static const int ADD_SIZE= 7;   // ADD_SIZE for TO,FROM,SUBJECT,CONTENT-TYPE,CONTENT-TRANSFER-ENCODING,CONETNT-DISPOSITION and \r\n
static const int SEND_BUF_SIZE= 54;
static char (*fileBuf)[CHARS] = NULL;
static const char cb64[]="ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
//end mail


//////// mysql connections settings
//const char *server="localhost";
//const char *user="root";
//const char *password="admin";
//const char *database="account_database";
//int query_state;
//std::string mysql_query_str = "";

// table variable for update data in table
Wt::WTable *ip_address_table;
Wt::WTable *phone_number_table;
Wt::WTable *subscriber_connected_table; // subscriber connected services table
Wt::WTable *service_table;
Wt::WTable *call_tariff_table;
// show tab tables
Wt::WTable *total_month_credit_table;
Wt::WTable *month_credit_table;
Wt::WTable *month_traffic_table;



// view subscriber varibles
// subscriber info variables
std::string subscriber_id_view_mode = "";

// create subscriber varibles
// subscriber group info variable
std::string group_name = "";

// subscriber info variables
std::string subscriber_id = "";
std::string group_id = "";
std::string name = "";
std::string surname = "";
std::string patronymic = "";
std::string full_name = "";
std::string subscriber_type = "";
std::string account_number = "";
std::string user_login = "";
std::string user_password = "";
std::string date_since = "";
std::string date_by = "";
std::string tariff_plan  = "";
std::string user_email = "";

// subscriber contacts data variables
std::string city = "";
std::string district = "";
std::string street = "";
std::string housing = "";
std::string house_floor = "";
std::string house = "";
std::string apartment = "";
std::string index_number = "";
std::string contact_numbers = "";

// subscriber requisites data variables
std::string personal_code = "";
std::string organization_code = "";
std::string tax_code = "";
std::string account = "";
std::string bank_code = "";
std::string agreement = "";
std::string agreement_date = "";

// subscriber information fields data variables
std::string description = "";
std::string information = "";



// edit subscriber variables
// subscriber group info variable
std::string group_name_edit_mode = "";
std::string new_group_name_edit_mode = ""; // used for edit tab when subscriber group changed name saved in this variable

// subscriber info variables
std::string subscriber_id_edit_mode = "";
std::string group_id_edit_mode = "";
std::string name_edit_mode = "";
std::string surname_edit_mode = "";
std::string patronymic_edit_mode = "";
std::string full_name_edit_mode = "";
std::string subscriber_type_edit_mode = "";
std::string account_number_edit_mode = "";
std::string user_login_edit_mode = "";
std::string user_password_edit_mode = "";
std::string date_since_edit_mode = "";
std::string date_by_edit_mode = "";
std::string tariff_plan_edit_mode  = "";
std::string user_email_edit_mode = "";

// subscriber contacts data variables
std::string city_edit_mode = "";
std::string district_edit_mode = "";
std::string street_edit_mode = "";
std::string housing_edit_mode = "";
std::string house_floor_edit_mode = "";
std::string house_edit_mode = "";
std::string apartment_edit_mode = "";
std::string index_number_edit_mode = "";
std::string contact_numbers_edit_mode = "";

// subscriber requisites data variables
std::string personal_code_edit_mode = "";
std::string organization_code_edit_mode = "";
std::string tax_code_edit_mode = "";
std::string account_edit_mode = "";
std::string bank_code_edit_mode = "";
std::string agreement_edit_mode = "";
std::string agreement_date_edit_mode = "";

// subscriber information fields data variables
std::string description_edit_mode = "";
std::string information_edit_mode = "";


//if we pushed fast month switch
extern void WtAccounts::month_button_fastswitch(int type){

	//ui->month_combo_box->currentIndex()+1;
       if (type==1){ui->month_combo_box->setCurrentIndex(ui->month_combo_box->currentIndex()+1);}
       if (type==2){ui->month_combo_box->setCurrentIndex(ui->month_combo_box->currentIndex()-1);}
	subscriber_fullName_changed();

}

extern void WtAccounts::checkIndex_TAB_close(int closedTABindex)
{

	if (closedTABindex>4)//check if its not 1 of main tabs was closed then destroy it from memory
	{
		Wt::WWidget* temp =  ui->main_tabs->widget(closedTABindex);
		ui->main_tabs->removeTab (temp);
		  delete temp;
    }
	//std::cout<<"NUMBER OF TABS _ > "<<ui->main_tabs->count()<<std::endl;


	//if all tabs are hiden then set welcome tab
	bool EN1=ui->main_tabs->isTabHidden(0),
		 EN2=ui->main_tabs->isTabHidden(1),
		 EN3=ui->main_tabs->isTabHidden(2),
		 EN4=ui->main_tabs->isTabHidden(3),
		 EN5=ui->main_tabs->isTabHidden(4);

     if (ui->main_tabs->count()==5 && EN1 && EN2 && EN3 && EN4 && EN5)
     {
    	 ui->welcome_user_tab_mi->setHidden(false);
    	 ui->main_tabs->setCurrentIndex(4);
     }


}
//
//extern void WtAccounts::edit_subscriber_load_data()
//{
//
//
//	ui->edit_user_tab_mi->setHidden(false);
//	//ui->main_tabs->setTabEnabled(0, 1);
//	ui->main_tabs->setCurrentIndex(2);
//
//	try{
//	mysql_init(&mysql);
//	conn=mysql_real_connect(&mysql, server, user, password, database, 0, 0, 0);
//	if(conn==NULL)
//	{
//	    std::cout<<mysql_error(&mysql)<<std::endl<<std::endl;
//	}
//	mysql_query(&mysql,"SET NAMES 'UTF8'");
//	if(conn==NULL)
//	{
//	    std::cout<<mysql_error(&mysql)<<std::endl<<std::endl;
//	}
//
//
///*
//// get main subscriber info and write in mysql table
//	//group_id = "1";
//	//Wt::WString temp =ui->user_full_name_edit->text().toUTF8();
//	full_name = ui->user_full_name_edit->text().toUTF8();
//	//full_name = boost::locale::conv::utf_to_utf<std::string>(ui->user_full_name_edit->text());
//	subscriber_type = ui->user_type_combo_box->currentText().toUTF8();
//	account_number = boost::lexical_cast<std::string>(ui->account_number_edit->text());
//	user_login = ui->user_login_edit->text().toUTF8();
//	user_password = ui->user_pass_edit->text().toUTF8();
//	tariff_plan = ui->tariff_plan_edit->text().toUTF8();
//	user_email = boost::lexical_cast<std::string>(ui->user_email_edit->text());
//
//	if (ui->user_include_date_checkbox->isChecked())
//	{
//		ui->user_include_date_date_edit->setFormat("yyyy-MM-dd");
//		date_since = boost::lexical_cast<std::string>(ui->user_include_date_date_edit->text());
//	}
//
//
//	if (ui->user_disable_date_checkbox->isChecked())
//	{
//		ui->user_disable_date_date_edit->setFormat("yyyy-MM-dd");
//		date_by = boost::lexical_cast<std::string>(ui->user_disable_date_date_edit->text());
//	}
//
//
//
//	std::cout << group_id << std::endl;
//	std::cout << name << std::endl;
//	std::cout << surname << std::endl;
//	std::cout << patronymic << std::endl;
//	std::cout << full_name << std::endl;
//	std::cout << subscriber_type << std::endl;
//	std::cout << account_number << std::endl;
//	std::cout << user_login << std::endl;
//	std::cout << user_password << std::endl;
//	std::cout << date_since << std::endl;
//	std::cout << date_by << std::endl;
//	std::cout << tariff_plan << std::endl;
//	std::cout << user_email << std::endl;
//
//
//
//*/
//
//
//
//
//// get data from mysql tables and load to form elements
//
//	std::string subscriber_name = "Джеред Локус Маккуин";
//
//
//	// get all data from mysql tables
//	std::string mysql_subscriber_all_table_data = "SELECT group_name, subscriber.subscriber_id, "
//			"subscriber.group_id, name, surname, patronymic, full_name, subscriber_type, "
//			"account_number, user_login, user_password, date_since, date_by, tariff_plan, "
//			"user_email, city, district, street, housing, floor, house, apartment, "
//			"index_number, contact_numbers, personal_code,organization_code, tax_code, "
//			"account, bank_code, agreement, agreement_date, description, information "
//			"FROM subscriber_group, subscriber, contacts, requisites, information_fields "
//			"WHERE subscriber.full_name = '"+subscriber_name+"' AND subscriber_group.group_id = subscriber.group_id "
//			"AND subscriber.subscriber_id = contacts.subscriber_id AND contacts.subscriber_id = requisites.subscriber_id "
//			"AND requisites.subscriber_id = information_fields.subscriber_id";
//
//	std::cout<<std::endl<<"query_state S1"<<std::endl;
//	query_state=mysql_query(conn, mysql_subscriber_all_table_data.c_str());
//	std::cout<<std::endl<<"query_state E1"<<std::endl;
//   } catch (const std::exception& e) {std::cout <<"query_state1 error -> "<< e.what()<<std::endl;}
//
//
//
//
///*
//	// get subscriber and group data
//	std::string mysql_subscriber_table_data = "SELECT subscriber_group.group_id,subscriber_group.group_name, subscriber_id, name, "
//			"surname, patronymic, full_name, subscriber_type, account_number, user_login, "
//			"user_password, date_since, date_by, tariff_plan, user_email "
//			"FROM subscriber_group, subscriber "
//			"WHERE (subscriber.full_name = '"+subscriber_name+"') AND (subscriber.group_id = subscriber_group.group_id)";
//
//	query_state=mysql_query(conn, mysql_subscriber_table_data.c_str());
//
//*/
//
//
//
//
//
//
//
//
//   try{
//	// set variables and form elements with data from mysql tables
//
//	if(query_state!=0)
//	{
//	   std::cout<<mysql_error(conn)<<std::endl<<std::endl;
//	}
//	res=mysql_store_result(conn);
//	std::cout<<"MySQL Values in the amaDB Table.1"<<std::endl<<std::endl;
//	row=mysql_fetch_row(res);
//
//
//	//std::cout << row[0] << " *****************************************************" << std::endl;
//	//std::cout << row[1] << " *****************************************************" << std::endl;
//	//std::cout << row[2] << " *****************************************************" << std::endl;
//
//// get all data from mysql tables
//
//	// subscriber group info variable
//	group_name = row[0];
//
//	// subscriber contacts data variables
//	subscriber_id = row[1];
//	group_id = row[2];
//	name = row[3];
//	surname = row[4];
//	patronymic = row[5];
//	full_name = row[6];
//	subscriber_type = row[7];
//	account_number = row[8];
//	user_login = row[9];
//	user_password = row[10];
//	date_since = row[11];
//	date_by = row[12];
//	tariff_plan  = row[13];
//	user_email = row[14];
//
//	// subscriber contacts data variables
//	city = row[15];
//	district = row[16];
//	street = row[17];
//	housing = row[18];
//	house_floor = row[19];
//	house = row[20];
//	apartment = row[21];
//	index_number = row[22];
//	contact_numbers = row[23];
//
//	// subscriber requisites data variables
//	personal_code = row[24];
//	organization_code = row[25];
//	tax_code = row[26];
//	account = row[27];
//	bank_code = row[28];
//	agreement = row[29];
//	agreement_date = row[30];
//
//	// subscriber information fields data variables
//	description = row[31];
//	information = row[32];
//
//	// subscriber and contacts form control data load
//	ui->user_type_combo_box_edit_user_tab->setValueText(Wt::WString::fromUTF8(subscriber_type));
//	ui->account_number_edit_edit_user_tab->setText(Wt::WString::fromUTF8(account_number));
//	ui->user_full_name_edit_edit_user_tab->setText(Wt::WString::fromUTF8(full_name));
//	ui->user_group_edit_edit_user_tab->setText(Wt::WString::fromUTF8(group_name));
//	ui->user_login_edit_edit_user_tab->setText(Wt::WString::fromUTF8(user_login));
//	ui->user_pass_edit_edit_user_tab->setText(Wt::WString::fromUTF8(user_password));
//
//	if(date_since == "" || date_since == "0000-00-00")
//	{
//		ui->user_include_date_checkbox_edit_user_tab->setChecked(true);
//		ui->user_include_date_date_edit_edit_user_tab->setText("");
//	}
//	else
//	{
//		ui->user_include_date_checkbox_edit_user_tab->setChecked(true);
//		ui->user_include_date_date_edit_edit_user_tab->setFormat("yyyy-MM-dd");
//		ui->user_include_date_date_edit_edit_user_tab->setText(Wt::WString::fromUTF8(date_since));
//	}
//
//	if(date_by == "" || date_by == "0000-00-00")
//	{
//		ui->user_disable_date_checkbox_edit_user_tab->setChecked(true);
//		ui->user_disable_date_date_edit_edit_user_tab->setText("");
//	}
//	else
//	{
//		ui->user_disable_date_checkbox_edit_user_tab->setChecked(true);
//		ui->user_disable_date_date_edit_edit_user_tab->setFormat("yyyy-MM-dd");
//		ui->user_disable_date_date_edit_edit_user_tab->setText(Wt::WString::fromUTF8(date_by));
//	}
//
//	ui->tariff_plan_edit_edit_user_tab->setText(Wt::WString::fromUTF8(tariff_plan));
//	ui->user_address_text_area_edit_user_tab->setText(Wt::WString::fromUTF8(city+ "\n" + district+ "\n" +
//			street+ "\n" + housing+ "\n" + house_floor+ "\n" +
//			house+ "\n" + apartment+ "\n" + index_number));
//	ui->user_email_edit_edit_user_tab->setText(Wt::WString::fromUTF8(user_email));
//	ui->contact_number_edit_edit_user_tab->setText(Wt::WString::fromUTF8(contact_numbers));
//
//	// requisite form control; load data
//	ui->personal_code_edit_edit_user_tab->setValueText(Wt::WString::fromUTF8(personal_code));
//	ui->organization_code_edit_edit_user_tab->setText(Wt::WString::fromUTF8(organization_code));
//	ui->tax_code_edit_edit_user_tab->setText(Wt::WString::fromUTF8(tax_code));
//	ui->requisite_account_edit_edit_user_tab->setText(Wt::WString::fromUTF8(account));
//	ui->bank_code_edit_edit_user_tab->setText(Wt::WString::fromUTF8(bank_code));
//	ui->agreement_edit_edit_user_tab->setText(Wt::WString::fromUTF8(agreement));
//
//	if(agreement_date == "" || agreement_date == "0000-00-00")
//	{
//		ui->agreement_checkbox_edit_user_tab->setChecked(true);
//		ui->agreement_date_edit_edit_user_tab->setText("");
//	}
//	else
//	{
//		ui->agreement_checkbox_edit_user_tab->setChecked(true);
//		ui->agreement_date_edit_edit_user_tab->setFormat("yyyy-MM-dd");
//		ui->agreement_date_edit_edit_user_tab->setText(Wt::WString::fromUTF8(agreement_date));
//	}
//
//	// information fields form control load data
//	ui->description_text_area_edit_user_tab->setText(Wt::WString::fromUTF8(description));
//	ui->information_text_area_edit_user_tab->setText(Wt::WString::fromUTF8(information));
//
//
//
//
//
//
//
//
//
//
//// clear all data variables
//
//	// subscriber group info variable
//	group_name = "";
//
//	// subscriber contacts data variables
//	subscriber_id = "";
//	group_id = "";
//	name = "";
//	surname = "";
//	patronymic = "";
//	full_name = "";
//	subscriber_type = "";
//	account_number = "";
//	user_login = "";
//	user_password = "";
//	date_since = "";
//	date_by = "";
//	tariff_plan  = "";
//	user_email = "";
//
//	// subscriber contacts data variables
//	city = "";
//	district = "";
//	street = "";
//	housing = "";
//	house_floor = "";
//	house = "";
//	apartment = "";
//	index_number = "";
//	contact_numbers = "";
//
//	// subscriber requisites data variables
//	personal_code = "";
//	organization_code = "";
//	tax_code = "";
//	account = "";
//	bank_code = "";
//	agreement = "";
//	agreement_date = "";
//
//	// subscriber information fields data variables
//	description = "";
//	information = "";
//
//	mysql_free_result(res);
//	mysql_close(conn);
//   } catch (const std::exception& e) {std::cout <<"query_stat23 error -> "<< e.what()<<std::endl;}
//}

//mail func





void encodeblock(unsigned char in[3], unsigned char out[4], int len)
{
    out[0] = cb64[ in[0] >> 2 ];
    out[1] = cb64[ ((in[0] & 0x03) << 4) | ((in[1] & 0xf0) >> 4) ];
    out[2] = (unsigned char) (len > 1 ? cb64[ ((in[1] & 0x0f) << 2) | ((in[2] & 0xc0) >> 6) ] : '=');
    out[3] = (unsigned char) (len > 2 ? cb64[ in[2] & 0x3f ] : '=');
}

void encode(FILE *infile, unsigned char *output_buf, int rowcount/*For Percent*/)
{
    unsigned char in[3], out[4];
        int i, len;
        *output_buf = 0;

    while(!feof(infile)) {
        len = 0;
        for(i = 0; i < 3; i++) {
            in[i] = (unsigned char) getc(infile);
            if(!feof(infile) ) {
                len++;
            }
            else {
                in[i] = 0;
            }
        }
        if(len) {
            encodeblock(in, out, len);
            strncat((char*)output_buf, (char*)out, 4);
        }
        }
}


struct fileBuf_upload_status
{
  int lines_read;
};

size_t read_file(std::string FROM, std::string TO, std::string FILENAME, std::string FILEPATH)
{
        FILE* hFile=NULL;
        size_t fileSize(0),len(0),buffer_size(0);

        //Open the file and make sure it exsits
        hFile = fopen(FILEPATH.c_str(),"rb");
        if(!hFile) {
                std::cout << "File not found!!!" << std::endl;
                exit (EXIT_FAILURE);
        }

        //Get filesize
        fseek(hFile,0,SEEK_END);
        fileSize = ftell(hFile);
        fseek(hFile,0,SEEK_SET);

        //Calculate the number of rows in Base64 encoded string
        //also calculate the size of the new char to be created
        //for the base64 encode string
        int no_of_rows = fileSize/SEND_BUF_SIZE + 1;
        int charsize = (no_of_rows*72)+(no_of_rows*2);

        //Base64 encode image and create encoded_buf string
        unsigned char* b64encode = new unsigned char[charsize];
        *b64encode = 0;
        encode(hFile, b64encode, no_of_rows /*For Percent*/);
        std::string encoded_buf = (char*)b64encode;

        // char TOO[] =  TO.c_str();

        //Create structure of email to be sent
        fileBuf = new char[ADD_SIZE + no_of_rows][CHARS];  //ADD_SIZE for TO,FROM,SUBJECT,CONTENT-TYPE,CONTENT-TRANSFER-
                                                           //ENCODING,CONETNT-DISPOSITION and \r\n
        std::string TO_str = "To: " + TO + "\r\n";
        strcpy(fileBuf[len++], TO_str.c_str());
        buffer_size += strlen(fileBuf[len-1]);

        std::string FROM_str = "From: " + FROM + "\r\n";
        strcpy(fileBuf[len++], FROM_str.c_str());
        buffer_size += strlen(fileBuf[len-1]);

        std::string Subject_str = "filename: " + FILEPATH + "\r\n";
        strcpy(fileBuf[len++], Subject_str.c_str());
        buffer_size += strlen(fileBuf[len-1]);

        std::string FILENAME_CT_str = "Content-Type: application/x-msdownload; name=\"" + FILENAME + "\"\r\n";
        strcpy(fileBuf[len++], FILENAME_CT_str.c_str());
        buffer_size += strlen(fileBuf[len-1]);

        strcpy(fileBuf[len++],"Content-Transfer-Encoding: base64\r\n");
        buffer_size += strlen(fileBuf[len-1]);

        std::string FILEPATH_CD_str = "Content-Disposition: attachment; filename=\"" + FILENAME + "\"\r\n";
        strcpy(fileBuf[len++],FILEPATH_CD_str.c_str());
        buffer_size += strlen(fileBuf[len-1]);

        strcpy(fileBuf[len++],"\r\n");
        buffer_size += strlen(fileBuf[len-1]);

        //This part attaches the Base64 encoded string and
        //sets the Base64 linesize to 72 characters + \r\n
        int pos = 0;
        std::string sub_encoded_buf;
        for(int i = 0; i <= no_of_rows-1; i++)
        {
                sub_encoded_buf = encoded_buf.substr(pos*72,72);  //Reads 72 characters at a time
                sub_encoded_buf += "\r\n";                        //and appends \r\n at the end
                strcpy(fileBuf[len++], sub_encoded_buf.c_str());  //copy the 72 characters & \r\n to email
                buffer_size += sub_encoded_buf.size();            //now increase the buffer_size
                pos++;                                            //finally increase pos by 1
        }


        delete[] b64encode;
        return buffer_size;
}


static size_t fileBuf_source(void *ptr, size_t size, size_t nmemb, void *userp)
{
        struct fileBuf_upload_status *upload_ctx = (struct fileBuf_upload_status *)userp;
        const char *fdata;

        if((size == 0) || (nmemb == 0) || ((size*nmemb) < 1))
        {
                return 0;
        }

        fdata = fileBuf[upload_ctx->lines_read];

        if(strcmp(fdata,""))
        {
                size_t len = strlen(fdata);
                memcpy(ptr, fdata, len);
                upload_ctx->lines_read++;
                return len;
        }
        return 0;
}


extern size_t WtAccounts::send_email(std::string FROM, std::string TO, std::string FILENAME, std::string FILEPATH)
{
	  CURL *curl;
	  CURLcode res = CURLE_OK;
	  struct curl_slist *recipients = NULL;
	  struct fileBuf_upload_status file_upload_ctx;
	  size_t file_size(0);

	  file_upload_ctx.lines_read = 0;

	  curl = curl_easy_init();
	  file_size = read_file(FROM, TO, FILENAME, FILEPATH);
	  if(curl)
	  {
	    curl_easy_setopt(curl, CURLOPT_USERNAME, "esep@automation-trade.com");
	    curl_easy_setopt(curl, CURLOPT_PASSWORD, "baywatch_ser1");
	    curl_easy_setopt(curl, CURLOPT_URL, "smtp://smtp.gmail.com:587"); // for google (gmail): smtp://smtp.gmail.com:587
	    curl_easy_setopt(curl, CURLOPT_USE_SSL, (long)CURLUSESSL_ALL);
	    //curl_easy_setopt(curl, CURLOPT_CAINFO, "cacert.pem");
	    curl_easy_setopt(curl, CURLOPT_MAIL_FROM, FROM.c_str());
	    recipients = curl_slist_append(recipients, TO.c_str());
	    curl_easy_setopt(curl, CURLOPT_MAIL_RCPT, recipients);
	    curl_easy_setopt(curl, CURLOPT_INFILESIZE, file_size);
	    curl_easy_setopt(curl, CURLOPT_READFUNCTION, fileBuf_source);
	    curl_easy_setopt(curl, CURLOPT_READDATA, &file_upload_ctx);
	    curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);
	    curl_easy_setopt(curl, CURLOPT_VERBOSE, 0); //Dont display Curl Connection data Change 1L to 0

	    res = curl_easy_perform(curl);

	    if(res != CURLE_OK)
	      fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
	    curl_slist_free_all(recipients);
	    curl_easy_cleanup(curl);
	  }
	  delete[] fileBuf;

	  return (int)res;
}
//end mail func

//PDF func
//Below is the "Rendering HTML to PDF" code from the widget gallery, with the new container widget for a target.
namespace {
    void HPDF_STDCALL error_handler(HPDF_STATUS error_no, HPDF_STATUS detail_no,
               void *user_data) {
    fprintf(stderr, "libharu error: error_no=%04X, detail_no=%d\n",
        (unsigned int) error_no, (int) detail_no);
    }
}

class ReportResource : public Wt::WResource
{
public:
	 std::string nate;
	 std::string nate2;
	 std::string nate3;
	 int number;
	 int state;
	 std::string css= "<style>table, th, td { border-collapse: collapse;border: 1px solid black;}</style>";
  ReportResource(Wt::WContainerWidget* target, Wt::WObject* parent = 0)
    : Wt::WResource(parent),
    _target(NULL)
  { state=1;
    suggestFileName("report.pdf");
    _target = target;

  }


//   ReportResource(Wt::WContainerWidget* target,int d=0)
//	     :number(d)
//	   {
//	     suggestFileName("report.pdf");
//	     _target = target;
//	   }

   ReportResource(Wt::WContainerWidget* target,std::string name="",std::string text="")
        :nate(name),nate2(text)
      {
  	std::string Obriv=" ";
  	std::size_t pos_for_Obriv;

  	//for addition name in tab
  	pos_for_Obriv = nate.find(' ');
  	Obriv += nate.substr(0,pos_for_Obriv);


        suggestFileName(Wt::WString::fromUTF8(Obriv)+".pdf");
        _target = target;
        state=2;
      }

/*
  ReportResource(Wt::WContainerWidget* target,std::string name="",std::string Number="",std::string rewq="")
      :nate(name),nate2(Number),nate3(rewq)
    {
	std::string Obriv=" ";
	std::size_t pos_for_Obriv;

	//for addition name in tab
	pos_for_Obriv = nate.find(' ');
	Obriv += nate.substr(0,pos_for_Obriv);


      suggestFileName(Wt::WString::fromUTF8(Obriv)+".pdf");
      _target = target;
    }
*/

  virtual void handleRequest(const Wt::Http::Request& request, Wt::Http::Response& response)
  {
    //response.setMimeType("application/pdf");

    HPDF_Doc pdf = HPDF_New(error_handler, 0);

	// Note: UTF-8 encoding (for TrueType fonts) is only available since libharu 2.3.0 !
	HPDF_UseUTFEncodings(pdf);


    renderReport(pdf);
    int ddsfd;


    HPDF_SaveToStream(pdf);


    unsigned int size = HPDF_GetStreamSize(pdf);
    HPDF_BYTE *buf = new HPDF_BYTE[size];
    HPDF_ReadFromStream (pdf, buf, &size);
    response.out().write((char*)buf, size);
    delete[] buf;


    HPDF_Free(pdf);

  }

public:

  Wt::WContainerWidget* _target;

  void renderReport(HPDF_Doc pdf)
  {

	if (state==1)  {
    std::stringstream ss;
//develop 007
    ss<<css;


    _target->htmlText(ss);
  //  size_t f =ss.str().find("height");
   // ss.str().erase (f,std::string("height:800.0px;").length());
   // std::cout<<f<<"FOUND  _target->htmlText(ss);"<<std::endl;
    std::string out = ss.str();
    std::string out_id = _target->id();
    std::string out_parent_id = _target->parent()->id();

    size_t f =out.find("height");
    out.erase (f,std::string("height:800.0px;").length());
    f =out.find("id=\"CHECK_user_treeTable\"");
    out.erase (f,std::string("id=-CHECK_user_treeTable-").length());

    f =out.find("id=\"CHECK_user_treeTableth\"");
    out.erase (f,std::string("id=-CHECK_user_treeTabletb-").length());
    f =out.find("id=\"CHECK_user_treeTabletb\"");
    out.erase (f,std::string("id=-CHECK_user_treeTabletb-").length());


    f =out.find("id=");
    while (f!=std::string::npos)
    {
    	//std::cout<<std::endl<<"FOUND "<<f<<std::endl;
    out.erase (f,std::string("id=-ofn8mge-").length());
    f =out.find("id=");
	}

//    f =out.find("Учет телефонных звонков");
//     while (f!=std::string::npos)
//     {
//     // std::cout<<std::endl<<"FOUND "<<f<<std::endl;
//      out.erase (f,std::string("Учет телефонных звонков").length());
//      f =out.find("Учет телефонных звонков");
//    }

//	     f =out.find("Обычный");
//	    	     while (f!=std::string::npos)
//	    	     {
//	    	     // std::cout<<std::endl<<"FOUND "<<f<<std::endl;
//	    	      out.erase (f,std::string("Обычный").length());
//	    	      f =out.find("Обычный");
//	    	  }

    std::ofstream out2("output.txt");
     out2 << out;
     out2.close();
    //std::string STRING;  //ss.str()
	 renderPdf(Wt::WString::fromUTF8(out), pdf);}
	else
  renderPdf(Wt::WString::fromUTF8(nate2), pdf);



  }

  void renderPdf(const Wt::WString& html, HPDF_Doc pdf)
  {

    HPDF_Page page = HPDF_AddPage(pdf);

     if (state==2 )HPDF_Page_SetSize(page, HPDF_PAGE_SIZE_A4, HPDF_PAGE_PORTRAIT);
     else
     HPDF_Page_SetSize(page, HPDF_PAGE_SIZE_A4, HPDF_PAGE_LANDSCAPE);

    int d;
    Wt::Render::WPdfRenderer renderer(pdf, page);

  //  if (state==1)renderer.useStyleSheet("/resources/Render.css");
   // if (state==1)renderer.useStyleSheet("Render.css");
   //renderer.setStyleSheetText(css);

//    const char *fontname;
//    HPDF_Font font;

 //   fontname = HPDF_LoadTTFontFromFile(pdf, "FreeSans.ttf", HPDF_TRUE);
 //   font = HPDF_GetFont(pdf, fontname, "UTF-8");
   // HPDF_Page_SetFontAndSize(page, font, 8);




    //renderer.st

    if (state==1){
  //renderer.setMargin(0);
  renderer.setDpi(110);
    }
  if (renderer.render(html))
  { std::cout<<std::endl<<"RENER OVER"<<std::endl;}
 std::cout<<std::endl<<"WAIT"<<std::endl;
  //HPDF_Page_EndText (page);
  //OUTput in file to test HTML
   if (state==2){

    nate+=".pdf";
    std::string patch_to_save_pdf= "/home/judge/Documents/";
    patch_to_save_pdf+=nate;
    const char *nametosave=patch_to_save_pdf.c_str();
    HPDF_SaveToFile (pdf, nametosave);
    std::cout<<"save pdf to file "<<std::endl;}
  //renderer.render(html);
  //HPDF_Page_BeginText (page);
  //HPDF_Page_MoveTextPos (page, 10, 10);

  }
};

//PDF func END

//creat pdf

extern void WtAccounts::creat_pdf_monthly(std::string name_ab,std::string text)
{

	HPDF_Doc pdf = HPDF_New(error_handler, 0);
	HPDF_UseUTFEncodings(pdf);
	HPDF_Page page = HPDF_AddPage(pdf);
	HPDF_Page_SetSize(page, HPDF_PAGE_SIZE_A4, HPDF_PAGE_PORTRAIT);
	Wt::Render::WPdfRenderer renderer(pdf, page);
	renderer.render(Wt::WString::fromUTF8(text));
	//name_ab=name_ab.substr(0,2);
	name_ab+=".pdf";
	std::string patch_to_save_pdf= "/home/judge/Documents/";
	patch_to_save_pdf+=name_ab;
	const char *nametosave=patch_to_save_pdf.c_str();
	HPDF_SaveToFile (pdf, nametosave);
	std::cout<<"save pdf to file new fucn"<<std::endl;

}



// zone fixed, clear function
// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

// function show required tab, depend on operation_name
extern void WtAccounts::subscriber_show_operation_tab(std::string operation_name)
{

	if (operation_name == "view") // *************************************************************************
	{
		//ui->user_account_tab_mi->setText("Adilbek Cool");
		ui->user_account_tab_mi->setHidden(false);
		//ui->main_tabs->setTabEnabled(0, 1);
		ui->main_tabs->setCurrentIndex(0);
		//ui->welcome_user_tab_mi->setHidden(true);




       try {
		mysql_init(&mysql);
		conn=mysql_real_connect(&mysql, server, user, password, database, 0, 0, 0);
		if(conn==NULL)
		{
		    std::cout<<mysql_error(&mysql)<<std::endl<<std::endl;
		}
		mysql_query(&mysql,"SET NAMES 'UTF8'");

		// left container set overflow and size
		//ui->user_account_left_container->setHeight(Wt::WLength("950px"));
		//ui->user_account_left_container->setOverflow(Wt::WContainerWidget::Overflow::OverflowAuto, Wt::Orientation::Vertical);


/*
		Wt::WContainerWidget *user_treeTable_container = new Wt::WContainerWidget(ui->user_account_left_container);
		user_treeTable_container->setHtmlTagName("div");
		user_treeTable_container->setWidth(Wt::WLength("100%"));
		user_treeTable_container->setHeight(Wt::WLength("700px"));
		//user_treeTable_container->setOverflow(Wt::WContainerWidget::Overflow::OverflowAuto, Wt::Orientation::Vertical);

		ui->user_treeTable = new Wt::WTreeTable(user_treeTable_container);
		ui->user_treeTable->setId("user_treeTable");
		ui->user_treeTable->setStyleClass(Wt::WString::fromUTF8("Wt-treetable"));
		ui->user_treeTable->setInline(0);


		//ui->user_treeTable->setStyleClass(Wt::WString::fromUTF8("Wt-treetable col-lg-12 col-md-12"));
		ui->user_treeTable->setStyleClass(Wt::WString::fromUTF8("Wt-treetable"));
		ui->user_treeTable->tree()->setSelectionMode(Wt::SingleSelection);
		//ui->user_treeTable->setWidth(Wt::WLength("70%"));
		//ui->user_treeTable->addColumn(Wt::WString::fromUTF8("Абонентов"), 100);

*/

	    ui->user_tree_root = new Wt::WTreeTableNode(Wt::WString::fromUTF8("ТОО"));
		ui->user_treeTable->setTreeRoot(ui->user_tree_root, Wt::WString::fromUTF8("Группа"));

	    Wt::WTreeTableNode *tree_node;

	// add node form mysql table
	    std::cout<<std::endl<<"query_state S2"<<std::endl;
		query_state=mysql_query(conn, "select * from subscriber_group ORDER BY group_name");

		if(query_state!=0)
		{
		   std::cout<<mysql_error(conn)<<std::endl<<std::endl;
		}
		res=mysql_store_result(conn);
		std::string mysql_get_subscriber_fullName = "";
		std::cout<<"MySQL Values in the amaDB Table.2"<<std::endl<<std::endl;
		std::cout<<std::endl<<"query_state E1"<<std::endl;
		while((row=mysql_fetch_row(res))!=NULL)
		{
			ui->user_tree_group  = new Wt::WTreeTableNode(Wt::WString::fromUTF8(row[1]), 0, ui->user_tree_root);
			ui->user_tree_group->setSelectable(false);
			std::cout<<std::endl<<"query_state S3"<<std::endl;
			mysql_get_subscriber_fullName = "select full_name from subscriber where subscriber.group_id = '"+boost::lexical_cast<std::string>(row[0])+"' ORDER BY full_name";
			query_state=mysql_query(conn, mysql_get_subscriber_fullName.c_str());
			if(query_state!=0)
			{
			   std::cout<<mysql_error(conn)<<std::endl<<std::endl;
			}
			std::cout<<std::endl<<"query_state E3"<<std::endl;
			add_res=mysql_store_result(conn);
			while((add_row=mysql_fetch_row(add_res))!=NULL)
			{
				//ui->user_tree_group ->setColumnWidget(1, new Wt::WText(Wt::WString::fromUTF8(add_row[0])));
				tree_node = new Wt::WTreeTableNode(Wt::WString::fromUTF8(add_row[0]), 0, ui->user_tree_group);
			}
		}

		mysql_free_result(res);
		mysql_free_result(add_res);
		mysql_close(conn);

		ui->user_tree_root->expand();



/*
		ui->user_treeTable->tree()->setSelectionMode(Wt::ExtendedSelection);
		ui->user_treeTable->addColumn(Wt::WString::fromUTF8("Номера"), 100);
		ui->user_treeTable->addColumn(Wt::WString::fromUTF8("Все номера"), 125);
		ui->user_treeTable->addColumn(Wt::WString::fromUTF8("Дата подк."), 125);
		ui->user_treeTable->addColumn(Wt::WString::fromUTF8("Дата откл."), 125);

		ui->user_tree_root = new Wt::WTreeTableNode(Wt::WString::fromUTF8("ТОО"));
		ui->user_treeTable->setTreeRoot(ui->user_tree_root, Wt::WString::fromUTF8("Абонент"));






		ui->user_tree_group = new Wt::WTreeTableNode(Wt::WString::fromUTF8("SIP Telecom"), 0, ui->user_tree_root);
		addNode(ui->user_tree_group, Wt::WString::fromUTF8("Ешимбетов Адильбек"), "423423", "127.0.0.1", "20.07/2016", "");
		addNode(ui->user_tree_group, Wt::WString::fromUTF8("Волошин Олег"), "534534", "190.165.257.130", "20.07.2016", "");
		addNode(ui->user_tree_group, Wt::WString::fromUTF8("Адам Ламберт"), "344556", "10.33.0.123", "20.07.2016", "");

		ui->user_tree_group = new Wt::WTreeTableNode("Digital System Servis", 0, ui->user_tree_root);


		ui->user_tree_group = new Wt::WTreeTableNode("KazTransCom", 0, ui->user_tree_root);


		ui->user_tree_root->expand();
*/



	// tables
	// ************************************************************************************************

		// total month credit table
/*
		ui->total_month_credit_table->clear();
		ui->total_month_credit_table->refresh();

		ui->total_month_credit_table->setHeaderCount(1);

		ui->total_month_credit_table->elementAt(0, 0)->addWidget(new Wt::WText(Wt::WString::fromUTF8("Услуга")));
		ui->total_month_credit_table->elementAt(0, 1)->addWidget(new Wt::WText(Wt::WString::fromUTF8("Код")));
		ui->total_month_credit_table->elementAt(0, 2)->addWidget(new Wt::WText(Wt::WString::fromUTF8("Количество")));
		ui->total_month_credit_table->elementAt(0, 3)->addWidget(new Wt::WText(Wt::WString::fromUTF8("Сумма")));
		ui->total_month_credit_table->elementAt(0, 4)->addWidget(new Wt::WText(Wt::WString::fromUTF8("Номер/IP")));
		ui->total_month_credit_table->elementAt(0, 5)->addWidget(new Wt::WText(Wt::WString::fromUTF8("Использование")));
		ui->total_month_credit_table->elementAt(0, 6)->addWidget(new Wt::WText(Wt::WString::fromUTF8("Описание")));

	    new Wt::WText(Wt::WString::fromUTF8("Абонентская плата за телефон"), ui->total_month_credit_table->elementAt(1, 0));
	    new Wt::WText(Wt::WString::fromUTF8("1.1"), ui->total_month_credit_table->elementAt(1, 1));
	    new Wt::WText(Wt::WString::fromUTF8("1"), ui->total_month_credit_table->elementAt(1, 2));
	    new Wt::WText(Wt::WString::fromUTF8("619.3500"), ui->total_month_credit_table->elementAt(1, 3));
	    new Wt::WText(Wt::WString::fromUTF8(""), ui->total_month_credit_table->elementAt(1, 4));
	    new Wt::WText(Wt::WString::fromUTF8("0"), ui->total_month_credit_table->elementAt(1, 5));
	    new Wt::WText(Wt::WString::fromUTF8(""), ui->total_month_credit_table->elementAt(1, 6));

		ui->total_month_credit_table->addStyleClass("table form-inline table-bordered table-hover table-condensed table-striped");

*/
       } catch (const std::exception& e) {std::cout <<"View error -> "<< e.what()<<std::endl;}
	} else if (operation_name == "create") // ****************************************************************
	{
		ui->create_user_tab_mi->setHidden(false);
		//ui->main_tabs->setTabEnabled(0, 1);
		ui->main_tabs->setCurrentIndex(1);
	} else // operation_name == "edit" ***********************************************************************
	{
		//ui->edit_user_tab_mi->setHidden(false);
		//ui->main_tabs->setTabEnabled(0, 1);
		//ui->main_tabs->setCurrentIndex(2);


		//ui->user_treeTable->tree()

      try{
	    Wt::WMessageBox *messageBox;
		std::string changedSubscriberName = "";
		Wt::WTreeNode *selected_node; // operator* returns contents of an interator
		std::set<Wt::WTreeNode* > highlightedRows = ui->user_treeTable->tree()->selectedNodes();
		if (!highlightedRows.empty())
		{
			ui->edit_user_tab_mi->setHidden(false);
			ui->main_tabs->setCurrentIndex(2);

			for (std::set<Wt::WTreeNode* >::iterator i = highlightedRows.begin(); i != highlightedRows.end(); ++i)
			{
			  selected_node = *i;
			}


			changedSubscriberName = selected_node->label()->text().toUTF8();

			highlightedRows.clear();






			mysql_init(&mysql);
			conn=mysql_real_connect(&mysql, server, user, password, database, 0, 0, 0);
			if(conn==NULL)
			{
				std::cout<<mysql_error(&mysql)<<std::endl<<std::endl;
			}
			mysql_query(&mysql,"SET NAMES 'UTF8'");
			if(conn==NULL)
			{
				std::cout<<mysql_error(&mysql)<<std::endl<<std::endl;
			}




// get data from mysql tables and load to form elements

			std::string subscriber_name = "Габриель Джек Питерсон";


			// get all data from mysql tables
			std::string mysql_subscriber_all_table_data = "SELECT group_name, subscriber.subscriber_id, "
					"subscriber.group_id, name, surname, patronymic, full_name, subscriber_type, "
					"account_number, user_login, user_password, date_since, date_by, tariff_plan, "
					"user_email, city, district, street, housing, floor, house, apartment, "
					"index_number, contact_numbers, personal_code,organization_code, tax_code, "
					"account, bank_code, agreement, agreement_date, description, information "
					"FROM subscriber_group, subscriber, contacts, requisites, information_fields "
					"WHERE subscriber.full_name = '"+changedSubscriberName+"' AND subscriber_group.group_id = subscriber.group_id "
					"AND subscriber.subscriber_id = contacts.subscriber_id AND contacts.subscriber_id = requisites.subscriber_id "
					"AND requisites.subscriber_id = information_fields.subscriber_id";
			std::cout<<std::endl<<"query_state S4"<<std::endl;
			query_state=mysql_query(conn, mysql_subscriber_all_table_data.c_str());






			// set variables and form elements with data from mysql tables

			if(query_state!=0)
			{
			   std::cout<<mysql_error(conn)<<std::endl<<std::endl;
			}
			res=mysql_store_result(conn);
			std::cout<<"MySQL Values in the amaDB Table.3"<<std::endl<<std::endl;
			row=mysql_fetch_row(res);
			std::cout<<std::endl<<"query_state E4"<<std::endl;

			//std::cout << row[0] << " *****************************************************" << std::endl;
			//std::cout << row[1] << " *****************************************************" << std::endl;
			//std::cout << row[2] << " *****************************************************" << std::endl;

// get all data from mysql tables

			// subscriber group info variable
			group_name_edit_mode = row[0];
			new_group_name_edit_mode = group_name_edit_mode;

			// subscriber contacts data variables
			subscriber_id_edit_mode = row[1];
			group_id_edit_mode = row[2];
			name_edit_mode= row[3];
			surname_edit_mode = row[4];
			patronymic_edit_mode = row[5];
			full_name_edit_mode = row[6];
			subscriber_type_edit_mode = row[7];
			account_number_edit_mode = row[8];
			user_login_edit_mode = row[9];
			user_password_edit_mode = row[10];
			date_since_edit_mode = row[11];
			date_by_edit_mode = row[12];
			tariff_plan_edit_mode  = row[13];
			user_email_edit_mode = row[14];

			// subscriber contacts data variables
			city_edit_mode = row[15];
			district_edit_mode = row[16];
			street_edit_mode = row[17];
			housing_edit_mode = row[18];
			house_floor_edit_mode = row[19];
			house_edit_mode = row[20];
			apartment_edit_mode = row[21];
			index_number_edit_mode = row[22];
			contact_numbers_edit_mode = row[23];

			// subscriber requisites data variables
			personal_code_edit_mode = row[24];
			organization_code_edit_mode = row[25];
			tax_code_edit_mode = row[26];
			account_edit_mode = row[27];
			bank_code_edit_mode = row[28];
			agreement_edit_mode = row[29];
			agreement_date_edit_mode = row[30];

			// subscriber information fields data variables
			description_edit_mode = row[31];
			information_edit_mode = row[32];

			// subscriber and contacts form control data load
			ui->user_type_combo_box_edit_user_tab->setValueText(Wt::WString::fromUTF8(subscriber_type_edit_mode));
			ui->account_number_edit_edit_user_tab->setText(Wt::WString::fromUTF8(account_number_edit_mode));
			ui->user_full_name_edit_edit_user_tab->setText(Wt::WString::fromUTF8(full_name_edit_mode));
			ui->user_group_edit_edit_user_tab->setText(Wt::WString::fromUTF8(group_name_edit_mode));
			ui->user_login_edit_edit_user_tab->setText(Wt::WString::fromUTF8(user_login_edit_mode));
			ui->user_pass_edit_edit_user_tab->setText(Wt::WString::fromUTF8(user_password_edit_mode));

			if(date_since_edit_mode == "" || date_since_edit_mode == "0000-00-00")
			{
				ui->user_include_date_checkbox_edit_user_tab->setChecked(false);
				ui->user_include_date_date_edit_edit_user_tab->setText("");
			}
			else
			{
				ui->user_include_date_checkbox_edit_user_tab->setChecked(true);
				ui->user_include_date_date_edit_edit_user_tab->setFormat("yyyy-MM-dd");
				ui->user_include_date_date_edit_edit_user_tab->setText(Wt::WString::fromUTF8(date_since_edit_mode));
			}

			if(date_by_edit_mode == "" || date_by_edit_mode == "0000-00-00")
			{
				ui->user_disable_date_checkbox_edit_user_tab->setChecked(false);
				ui->user_disable_date_date_edit_edit_user_tab->setText("");
			}
			else
			{
				ui->user_disable_date_checkbox_edit_user_tab->setChecked(true);
				ui->user_disable_date_date_edit_edit_user_tab->setFormat("yyyy-MM-dd");
				ui->user_disable_date_date_edit_edit_user_tab->setText(Wt::WString::fromUTF8(date_by_edit_mode));
			}

			ui->tariff_plan_edit_edit_user_tab->setText(Wt::WString::fromUTF8(tariff_plan_edit_mode));
			ui->user_address_text_area_edit_user_tab->setText(Wt::WString::fromUTF8("Город: " + city_edit_mode + "\n" + "Район: " + district_edit_mode+ "\n" +
					"Улица: " + street_edit_mode+ "\n" + "Корпус: " + housing_edit_mode+ "\n" + "Этаж:" + house_floor_edit_mode+ "\n" +
					"Дом:" + house_edit_mode+ "\n" + "Квартира: " + apartment_edit_mode+ "\n" + "Индекс: " + index_number_edit_mode));
			ui->user_email_edit_edit_user_tab->setText(Wt::WString::fromUTF8(user_email_edit_mode));
			ui->contact_number_edit_edit_user_tab->setText(Wt::WString::fromUTF8(contact_numbers_edit_mode));




			// ip_adreess entry load data
			std::string mysql_get_ip_address = "SELECT ip_address FROM ip_addresses WHERE ip_addresses.subscriber_id = '"+subscriber_id_edit_mode+"'";
			query_state=mysql_query(conn, mysql_get_ip_address.c_str());

			std::string new_ip_addresses = "";
			if(query_state!=0)
			{
			   std::cout<<mysql_error(conn)<<std::endl<<std::endl;
			}
			res=mysql_store_result(conn);
			row=mysql_fetch_row(res);
			while(row!=NULL)
			{
				new_ip_addresses.append(row[0]);
				row=mysql_fetch_row(res);
				if (row!=NULL)
				{
					new_ip_addresses.append(", ");
				}
			}

			ui->ip_login_edit_edit_user_tab->setText(Wt::WString::fromUTF8(new_ip_addresses));





			std::cout<<std::endl<<"query_state S5"<<std::endl;
			// phone number entry load data
			std::string mysql_get_phone_numbers = "SELECT number FROM phone_numbers WHERE phone_numbers.subscriber_id = '"+subscriber_id_edit_mode+"'";
			query_state=mysql_query(conn, mysql_get_phone_numbers.c_str());

			std::string new_phone_numbers= "";
			if(query_state!=0)
			{
			   std::cout<<mysql_error(conn)<<std::endl<<std::endl;
			}
			res=mysql_store_result(conn);
			row=mysql_fetch_row(res);
			while(row!=NULL)
			{
				new_phone_numbers.append(row[0]);
				row=mysql_fetch_row(res);
				if (row!=NULL)
				{
					new_phone_numbers.append(", ");
				}
			}
			std::cout<<std::endl<<"query_state E5"<<std::endl;
			ui->user_number_edit_edit_user_tab->setText(Wt::WString::fromUTF8(new_phone_numbers));





			// requisite form control load data
			ui->personal_code_edit_edit_user_tab->setValueText(Wt::WString::fromUTF8(personal_code_edit_mode));
			ui->organization_code_edit_edit_user_tab->setText(Wt::WString::fromUTF8(organization_code_edit_mode));
			ui->tax_code_edit_edit_user_tab->setText(Wt::WString::fromUTF8(tax_code_edit_mode));
			ui->requisite_account_edit_edit_user_tab->setText(Wt::WString::fromUTF8(account_edit_mode));
			ui->bank_code_edit_edit_user_tab->setText(Wt::WString::fromUTF8(bank_code_edit_mode));
			ui->agreement_edit_edit_user_tab->setText(Wt::WString::fromUTF8(agreement_edit_mode));

			if(agreement_date_edit_mode == "" || agreement_date_edit_mode == "0000-00-00")
			{
				ui->agreement_checkbox_edit_user_tab->setChecked(false);
				ui->agreement_date_edit_edit_user_tab->setText("");
			}
			else
			{
				ui->agreement_checkbox_edit_user_tab->setChecked(true);
				ui->agreement_date_edit_edit_user_tab->setFormat("yyyy-MM-dd");
				ui->agreement_date_edit_edit_user_tab->setText(Wt::WString::fromUTF8(agreement_date_edit_mode));
			}

			// information fields form control load data
			ui->description_text_area_edit_user_tab->setText(Wt::WString::fromUTF8(description_edit_mode));
			ui->information_text_area_edit_user_tab->setText(Wt::WString::fromUTF8(information_edit_mode));


/*
// clear all data variables

			// subscriber group info variable
			group_name_edit_mode = "";

			// subscriber contacts data variables
			subscriber_id_edit_mode = "";
			group_id_edit_mode = "";
			name_edit_mode = "";
			surname_edit_mode = "";
			patronymic_edit_mode = "";
			full_name_edit_mode = "";
			subscriber_type_edit_mode = "";
			account_number_edit_mode = "";
			user_login_edit_mode = "";
			user_password_edit_mode = "";
			date_since_edit_mode = "";
			date_by_edit_mode = "";
			tariff_plan_edit_mode  = "";
			user_email_edit_mode = "";

			// subscriber contacts data variables
			city_edit_mode = "";
			district_edit_mode = "";
			street_edit_mode = "";
			housing_edit_mode = "";
			house_floor_edit_mode = "";
			house_edit_mode = "";
			apartment_edit_mode = "";
			index_number_edit_mode = "";
			contact_numbers_edit_mode = "";

			// subscriber requisites data variables
			personal_code_edit_mode = "";
			organization_code_edit_mode = "";
			tax_code_edit_mode = "";
			account_edit_mode = "";
			bank_code_edit_mode = "";
			agreement_edit_mode = "";
			agreement_date_edit_mode = "";

			// subscriber information fields data variables
			description_edit_mode = "";
			information_edit_mode = "";
*/
			mysql_free_result(res);
			mysql_close(conn);

		} else
		{
			messageBox = new Wt::WMessageBox(Wt::WString::fromUTF8("Ошибка"), Wt::WString::fromUTF8("Не выбран абонент"), Wt::Information, Wt::Yes | Wt::No);
			messageBox->buttonClicked().connect(std::bind([=] () {
			delete messageBox;
			}));

			messageBox->show();
		}
	 } catch (const std::exception& e) {std::cout <<"View2 error -> "<< e.what()<<std::endl;}
	}


}





// dialog window for enter subscriber full name
extern void WtAccounts::subscriber_name_dialog(std::string operation_name)
{
	try{
    Wt::WDialog *dialog = new Wt::WDialog(Wt::WString::fromUTF8("Абонент"));

    dialog->resize(500, 350);

    Wt::WLabel *surname_label = new Wt::WLabel(Wt::WString::fromUTF8("Фамилия"),
				       dialog->contents());
    surname_label->setStyleClass("col-lg-4 col-md-4 top_pad");

    Wt::WContainerWidget *surname_edit_container = new Wt::WContainerWidget(dialog->contents());
    surname_edit_container->setStyleClass(Wt::WString::fromUTF8("col-md-8 col-lg-8"));
    surname_edit_container->setHtmlTagName("div");

    Wt::WLineEdit *surname_edit = new Wt::WLineEdit(surname_edit_container);
    surname_label->setBuddy(surname_edit);



    Wt::WLabel *name_label = new Wt::WLabel(Wt::WString::fromUTF8("Имя"),
				       dialog->contents());
    name_label->setStyleClass("col-lg-4 col-md-4 top_mar top_pad");

    Wt::WContainerWidget *name_edit_container = new Wt::WContainerWidget(dialog->contents());
    name_edit_container->setStyleClass(Wt::WString::fromUTF8("col-md-8 col-lg-8 top_mar"));
    name_edit_container->setHtmlTagName("div");
    Wt::WLineEdit *name_edit = new Wt::WLineEdit(name_edit_container);
    name_label->setBuddy(name_edit);



    Wt::WLabel *family_name_label = new Wt::WLabel(Wt::WString::fromUTF8("Отчество"),
				       dialog->contents());
    family_name_label->setStyleClass("col-lg-4 col-md-4 top_mar top_pad");

    Wt::WContainerWidget *family_name_edit_container = new Wt::WContainerWidget(dialog->contents());
    family_name_edit_container->setStyleClass(Wt::WString::fromUTF8("col-md-8 col-lg-8 top_mar"));
    family_name_edit_container->setHtmlTagName("div");
    Wt::WLineEdit *family_name_edit = new Wt::WLineEdit(family_name_edit_container);
    family_name_label->setBuddy(family_name_edit);



    Wt::WLabel *full_name_label = new Wt::WLabel(Wt::WString::fromUTF8("Полное имя"),
				       dialog->contents());
    full_name_label->setStyleClass("col-lg-4 col-md-4 top_mar top_pad");

    Wt::WContainerWidget *full_name_edit_container = new Wt::WContainerWidget(dialog->contents());
    full_name_edit_container->setStyleClass(Wt::WString::fromUTF8("col-md-8 col-lg-8 top_mar"));
    full_name_edit_container->setHtmlTagName("div");
    Wt::WLineEdit *full_name_edit = new Wt::WLineEdit(full_name_edit_container);
    full_name_label->setBuddy(full_name_edit);

    // if edit mode then we fill dialog window entries with subscriber name info
    if(operation_name == "edit")
    {
    	surname_edit->setText(Wt::WString::fromUTF8(surname_edit_mode));
        name_edit->setText(Wt::WString::fromUTF8(name_edit_mode));
        family_name_edit->setText(Wt::WString::fromUTF8(patronymic_edit_mode));
        full_name_edit->setText(Wt::WString::fromUTF8(full_name_edit_mode));

    }


    dialog->contents()->addStyleClass("form-group");



    /*
    Wt::WRegExpValidator *validator =
        new Wt::WRegExpValidator("[A-Za-z][1-9][0-9]{0,2}");
    validator->setMandatory(true);
    edit->setValidator(validator);
     */
    Wt::WPushButton *ok = new Wt::WPushButton("OK", dialog->footer());
    ok->setDefault(true);
    //if (wApp->environment().ajax())
     // ok->disable();

    Wt::WPushButton *cancel = new Wt::WPushButton("Cancel", dialog->footer());
    dialog->rejectWhenEscapePressed();

    /*edit->keyWentUp().connect(std::bind([=] () {
	ok->setDisabled(edit->validate() != Wt::WValidator::Valid);
    }));*/

    /*
     * Accept the dialog
     */
    ok->clicked().connect(std::bind([=] () {
	//if (edit->validate())
	    dialog->accept();
    }));

    /*
     * Reject the dialog
     */
    cancel->clicked().connect(dialog, &Wt::WDialog::reject);

    /*
     * Process the dialog result.
     */
    dialog->finished().connect(std::bind([=] () {
	if (dialog->result() == Wt::WDialog::Accepted)
	{   try{
		if (operation_name == "create")
		{
			name = name_edit->text().toUTF8();
			surname = surname_edit->text().toUTF8();
			patronymic = family_name_edit->text().toUTF8();
			ui->user_full_name_edit->setText(surname_edit->text() + " " + name_edit->text() + " " + family_name_edit->text());
		} else // operation_name == "edit"
		{
			if (name_edit->text() != "") name_edit_mode = name_edit->text().toUTF8();
			if (surname_edit->text() != "") surname_edit_mode = surname_edit->text().toUTF8();
			if (family_name_edit->text() != "") patronymic_edit_mode = family_name_edit->text().toUTF8();
			ui->user_full_name_edit_edit_user_tab->setText(Wt::WString::fromUTF8(surname_edit_mode) + " " + Wt::WString::fromUTF8(name_edit_mode) + " " + Wt::WString::fromUTF8(patronymic_edit_mode));
		}} catch (const std::exception& e) {std::cout <<"operator creat 2 -> "<< e.what()<<std::endl;}
	}

	delete dialog;
    }));

    dialog->show();
} catch (const std::exception& e) {std::cout <<"Operator creat 1 -> "<< e.what()<<std::endl;}
}





// show dialog window where we can chose subscriber group
extern void WtAccounts::subscriber_group_dialog(std::string operation_name)
{   try{
	mysql_init(&mysql);
	conn=mysql_real_connect(&mysql, server, user, password, database, 0, 0, 0);
	if(conn==NULL)
	{
	    std::cout<<mysql_error(&mysql)<<std::endl<<std::endl;
	}
	mysql_query(&mysql,"SET NAMES 'UTF8'");

    Wt::WDialog *dialog = new Wt::WDialog(Wt::WString::fromUTF8("Выберите группу абонента:"));

    dialog->resize(500, 650);

// dialog contents
    Wt::WTreeTable *treeTable;
	treeTable = new Wt::WTreeTable(dialog->contents());
    //treeTable->resize(650, 300);
    treeTable->setStyleClass(Wt::WString::fromUTF8("Wt-treetable col-lg-12 col-md-12"));
    treeTable->tree()->setSelectionMode(Wt::SingleSelection);
    treeTable->addColumn(Wt::WString::fromUTF8("Абонентов"), 100);

    Wt::WTreeTableNode *tree_root;
	tree_root = new Wt::WTreeTableNode(Wt::WString::fromUTF8("ТОО"));
    treeTable->setTreeRoot(tree_root, Wt::WString::fromUTF8("Группа"));

    Wt::WTreeTableNode *tree_node;

// add node form mysql table
	query_state=mysql_query(conn, "select * from subscriber_group");
	if(query_state!=0)
	{
	   std::cout<<mysql_error(conn)<<std::endl<<std::endl;
	}
	res=mysql_store_result(conn);
	std::cout<<"MySQL Values in the amaDB Table.4"<<std::endl<<std::endl;
	while((row=mysql_fetch_row(res))!=NULL)
	{
		tree_node  = new Wt::WTreeTableNode(Wt::WString::fromUTF8(row[1]), 0, tree_root);
		tree_node ->setColumnWidget(1, new Wt::WText(Wt::WString::fromUTF8(row[2])));
	}

	mysql_free_result(res);
	mysql_close(conn);

	tree_root->expand();



// dialog footer
    Wt::WPushButton *ok = new Wt::WPushButton("OK", dialog->footer());
    ok->setDefault(true);


    Wt::WPushButton *cancel = new Wt::WPushButton("Cancel", dialog->footer());
    dialog->rejectWhenEscapePressed();


    /*
     * Accept the dialog
     */
    ok->clicked().connect(std::bind([=] () {
	    dialog->accept();
    }));

    /*
     * Reject the dialog
     */
    cancel->clicked().connect(dialog, &Wt::WDialog::reject);

    /*
     * Process the dialog result.
     */
    dialog->finished().connect(std::bind([=] () {
	if (dialog->result() == Wt::WDialog::Accepted)
	{
		Wt::WTreeNode *selected_node; // operator* returns contents of an interator
		std::set<Wt::WTreeNode* > highlightedRows = treeTable->tree()->selectedNodes();
		if (!highlightedRows.empty())
		{
			for (std::set<Wt::WTreeNode* >::iterator i = highlightedRows.begin(); i != highlightedRows.end(); ++i)
			{
			  selected_node = *i;
			}
			if (operation_name == "create")
			{
				ui->user_group_edit->setText(selected_node->label()->text());
				group_name = selected_node->label()->text().toUTF8();
			} else // operation_name == "edit"
			{
				ui->user_group_edit_edit_user_tab->setText(selected_node->label()->text());
				new_group_name_edit_mode = selected_node->label()->text().toUTF8();
			}
			highlightedRows.clear();
		}
	}

	delete dialog;
    }));


    dialog->show();
} catch (const std::exception& e) {std::cout <<"subscriber_group_dialog -> "<< e.what()<<std::endl;}
}





// show dialog window where you create new phone numbers
extern void WtAccounts::create_phone_number_dialog(std::string operation_name)
{

	try {
    Wt::WDialog *dialog = new Wt::WDialog(Wt::WString::fromUTF8("Новый телефонный номер"));

    dialog->resize(600, 550);



	mysql_init(&mysql);
	conn=mysql_real_connect(&mysql, server, user, password, database, 0, 0, 0);
	/*
	if(conn==NULL)
	{
	    std::cout<<mysql_error(&mysql)<<std::endl<<std::endl;
	}
	 */
	mysql_query(&mysql,"SET NAMES 'UTF8'");



    // device label and edit
    Wt::WLabel *device_label = new Wt::WLabel(Wt::WString::fromUTF8("Устройство"),
    				       dialog->contents());
    device_label->setStyleClass("col-lg-3 col-md-3 top_pad top_mar");

    Wt::WContainerWidget *device_edit_container = new Wt::WContainerWidget(dialog->contents());
    device_edit_container->setStyleClass(Wt::WString::fromUTF8("col-md-9 col-lg-9 top_mar"));
    device_edit_container->setHtmlTagName("div");

    Wt::WLineEdit *device_edit = new Wt::WLineEdit(device_edit_container);
    device_edit->setText(Wt::WString::fromUTF8("Учет телефонных вызовов"));
    device_label->setBuddy(device_edit);



    // range label and combo box
    Wt::WLabel *range_label = new Wt::WLabel(Wt::WString::fromUTF8("Диапазон"),
    				       dialog->contents());
    range_label->setStyleClass("col-lg-3 col-md-3 top_pad top_mar");

    Wt::WContainerWidget *range_combobox_container = new Wt::WContainerWidget(dialog->contents());
    range_combobox_container->setStyleClass(Wt::WString::fromUTF8("col-md-9 col-lg-9 top_mar"));
    range_combobox_container->setHtmlTagName("div");

    Wt::WComboBox *range_combobox = new Wt::WComboBox(range_combobox_container);
    range_label->setBuddy(range_combobox);



    // number label and two edit
    Wt::WLabel *number_label = new Wt::WLabel(Wt::WString::fromUTF8("Номер"),
    				       dialog->contents());
    number_label->setStyleClass("col-lg-3 col-md-3 top_pad top_mar");


    Wt::WContainerWidget *number_prefix_edit_container = new Wt::WContainerWidget(dialog->contents());
    number_prefix_edit_container->setStyleClass(Wt::WString::fromUTF8("col-md-2 col-lg-2 top_mar"));
    number_prefix_edit_container->setHtmlTagName("div");

    Wt::WLineEdit *number_prefix_edit = new Wt::WLineEdit(number_prefix_edit_container);

    Wt::WContainerWidget *number_edit_container = new Wt::WContainerWidget(dialog->contents());
    number_edit_container->setStyleClass(Wt::WString::fromUTF8("col-md-7 col-lg-7 top_mar"));
    number_edit_container->setHtmlTagName("div");

    Wt::WLineEdit *number_edit = new Wt::WLineEdit(number_edit_container);
    number_label->setBuddy(number_edit);



    // description label and text area
    Wt::WLabel *description_label = new Wt::WLabel(Wt::WString::fromUTF8("Описание"),
    				       dialog->contents());
    description_label->setStyleClass("col-lg-3 col-md-3 top_pad top_mar");

    Wt::WContainerWidget *description_text_area_container = new Wt::WContainerWidget(dialog->contents());
    description_text_area_container->setStyleClass(Wt::WString::fromUTF8("col-md-9 col-lg-9 top_mar"));
    description_text_area_container->setHtmlTagName("div");

    Wt::WTextArea *description_text_area = new Wt::WTextArea(description_text_area_container);
    description_text_area->setColumns(80);
    description_text_area->setRows(3);
    description_label->setBuddy(description_text_area);



    // include date label, check box and date edit
    Wt::WLabel *include_date_label = new Wt::WLabel(Wt::WString::fromUTF8("Включен с"),
    				       dialog->contents());
    include_date_label->setStyleClass("col-lg-3 col-md-3 top_pad top_mar");


    Wt::WCheckBox *include_date_checkbox = new Wt::WCheckBox("", dialog->contents());
    include_date_checkbox->setStyleClass("col-lg-1 col-md-1 top_pad");

    Wt::WContainerWidget *include_date_edit_container = new Wt::WContainerWidget(dialog->contents());
    include_date_edit_container->setStyleClass(Wt::WString::fromUTF8("col-md-8 col-lg-8 top_mar"));
    include_date_edit_container->setHtmlTagName("div");

    Wt::WDateEdit *include_date_edit = new Wt::WDateEdit(include_date_edit_container);
    include_date_edit->setFormat("yyyy-MM-dd");
    include_date_label->setBuddy(include_date_edit);



    // disable date label, check box and date edit
    Wt::WLabel *disable_date_label = new Wt::WLabel(Wt::WString::fromUTF8("По"),
    				       dialog->contents());
    disable_date_label->setStyleClass("col-lg-3 col-md-3 top_pad top_mar");


    Wt::WCheckBox *disable_date_checkbox = new Wt::WCheckBox("", dialog->contents());
    disable_date_checkbox->setStyleClass("col-lg-1 col-md-1 top_pad");

    Wt::WContainerWidget *disable_date_edit_container = new Wt::WContainerWidget(dialog->contents());
    disable_date_edit_container->setStyleClass(Wt::WString::fromUTF8("col-md-8 col-lg-8 top_mar"));
    disable_date_edit_container->setHtmlTagName("div");

    Wt::WDateEdit *disable_date_edit = new Wt::WDateEdit(disable_date_edit_container);
    disable_date_edit->setFormat("yyyy-MM-dd");
    disable_date_label->setBuddy(disable_date_edit);



    // tariff plan label and combo box
    Wt::WLabel *tariff_plan_label = new Wt::WLabel(Wt::WString::fromUTF8("Тарифный план"),
    				       dialog->contents());
    tariff_plan_label->setStyleClass("col-lg-3 col-md-3 top_pad");

    Wt::WContainerWidget *tariff_plan_combobox_container = new Wt::WContainerWidget(dialog->contents());
    tariff_plan_combobox_container->setStyleClass(Wt::WString::fromUTF8("col-md-9 col-lg-9 top_mar"));
    tariff_plan_combobox_container->setHtmlTagName("div");

    Wt::WComboBox *tariff_plan_combobox = new Wt::WComboBox(tariff_plan_combobox_container);
    tariff_plan_label->setBuddy(tariff_plan_combobox);

    query_state=mysql_query(conn, "SELECT plan_name FROM tariff_plan");

	if(query_state!=0)
	{
	   std::cout<<mysql_error(conn)<<std::endl<<std::endl;
	}
	res=mysql_store_result(conn);
	while((row=mysql_fetch_row(res))!=NULL)
	{
		tariff_plan_combobox->addItem(Wt::WString::fromUTF8(row[0]));
	}

	mysql_free_result(res);
	mysql_close(conn);

    dialog->contents()->addStyleClass("form-group");



    Wt::WPushButton *ok = new Wt::WPushButton("OK", dialog->footer());
    ok->setDefault(true);


    Wt::WPushButton *cancel = new Wt::WPushButton("Cancel", dialog->footer());
    dialog->rejectWhenEscapePressed();



    // Accept the dialog
    ok->clicked().connect(std::bind([=] () {
	    dialog->accept();
    }));


    // Reject the dialog
    cancel->clicked().connect(dialog, &Wt::WDialog::reject);


    // Process the dialog result.
    dialog->finished().connect(std::bind([=] () {
	if (dialog->result() == Wt::WDialog::Accepted)
	{


		mysql_init(&mysql);
		conn=mysql_real_connect(&mysql, server, user, password, database, 0, 0, 0);
		/*
		if(conn==NULL)
		{
		    std::cout<<mysql_error(&mysql)<<std::endl<<std::endl;
		}
		 */
		mysql_query(&mysql,"SET NAMES 'UTF8'");


		std::string device = device_edit->text().toUTF8();
		std::string number = (number_prefix_edit->text() + number_edit->text()).toUTF8();
		std::string description = description_text_area->text().toUTF8();

		std::string date_since = "";
		if (include_date_checkbox->isChecked())
		{
			date_since = boost::lexical_cast<std::string>(include_date_edit->text());
		}

		std::string date_by = "";
		if (disable_date_checkbox->isChecked())
		{
			date_by = boost::lexical_cast<std::string>(disable_date_edit->text());
		}

		std::string tariff_plan = tariff_plan_combobox->currentText().toUTF8();

		std::string mysql_insert_new_number = "";

		if (operation_name == "create")
		{
			mysql_insert_new_number = "insert into phone_numbers (subscriber_id, device, number, "
					"description, date_since, date_by, tariff_plan, number_status)  "
					"values (NULL, '"+device+"', '"+number+"', '"+description+"', '"+date_since+"', "
							"'"+date_by+"', '"+tariff_plan+"', 'not_processed')";
		} else // operation_name == "edit"
		{
			mysql_insert_new_number = "insert into phone_numbers (subscriber_id, device, number, "
					"description, date_since, date_by, tariff_plan, number_status)  "
					"values ('"+subscriber_id_edit_mode+"', '"+device+"', '"+number+"', '"+description+"', '"+date_since+"', "
							"'"+date_by+"', '"+tariff_plan+"', 'processed')";
		}

		query_state=mysql_query(conn, mysql_insert_new_number.c_str());
		//query_state=mysql_query(conn, "select device, ip_address, description, date_since, date_by, "
		//							  "tariff_plan from ip_addresses where ip_addresses.ip_status = '"not_processed"'");
		if(query_state!=0)
		{
		   std::cout<<mysql_error(conn)<<std::endl<<std::endl;
		}


		phone_number_table->clear();
		phone_number_table->elementAt(0, 0)->addWidget(new Wt::WText(Wt::WString::fromUTF8("Номер")));
		phone_number_table->elementAt(0, 1)->addWidget(new Wt::WText(Wt::WString::fromUTF8("Устройство")));
		phone_number_table->elementAt(0, 2)->addWidget(new Wt::WText(Wt::WString::fromUTF8("С")));
		phone_number_table->elementAt(0, 3)->addWidget(new Wt::WText(Wt::WString::fromUTF8("По")));
		phone_number_table->elementAt(0, 4)->addWidget(new Wt::WText(Wt::WString::fromUTF8("Тарифный план")));
		phone_number_table->elementAt(0, 5)->addWidget(new Wt::WText(Wt::WString::fromUTF8("Описание")));

		int row_number = 0;


		std::string mysql_phone_number_table_data = "";

		if (operation_name == "create")
		{
			mysql_phone_number_table_data = "select device, number, description, date_since, date_by, "
					  "tariff_plan from phone_numbers where phone_numbers.number_status = 'not_processed'";
		} else // operation_name == "edit"
		{
			mysql_phone_number_table_data = "select device, number, description, date_since, date_by, "
					  "tariff_plan from phone_numbers where phone_numbers.subscriber_id = '"+subscriber_id_edit_mode+"'";
		}


		query_state=mysql_query(conn, mysql_phone_number_table_data.c_str());
		//query_state=mysql_query(conn, "select device, ip_address, description, date_since, date_by, "
		//							  "tariff_plan from ip_addresses where ip_addresses.ip_status = '"not_processed"'");
		if(query_state!=0)
		{
		   std::cout<<mysql_error(conn)<<std::endl<<std::endl;
		}
		res=mysql_store_result(conn);
		while((row=mysql_fetch_row(res))!=NULL)
		{
			row_number++;
			new Wt::WText(Wt::WString::fromUTF8(row[1]), phone_number_table->elementAt(row_number, 0));
			new Wt::WText(Wt::WString::fromUTF8(row[0]), phone_number_table->elementAt(row_number, 1));
			new Wt::WText(Wt::WString::fromUTF8(row[3]), phone_number_table->elementAt(row_number, 2));
			new Wt::WText(Wt::WString::fromUTF8(row[4]), phone_number_table->elementAt(row_number, 3));
			new Wt::WText(Wt::WString::fromUTF8(row[5]), phone_number_table->elementAt(row_number, 4));
			new Wt::WText(Wt::WString::fromUTF8(row[2]), phone_number_table->elementAt(row_number, 5));
		}
		phone_number_table->refresh();
		mysql_free_result(res);
		mysql_close(conn);
	}
	else
	{
	}

	delete dialog;
    }));

    dialog->show();

	} catch (const std::exception& e) {std::cout <<"create_phone_number_dialog -> "<< e.what()<<std::endl;}
}





// show dialog window where you delete exist phone numbers
extern void WtAccounts::delete_phone_number_dialog(std::string operation_name)
{
    Wt::WDialog *dialog = new Wt::WDialog(Wt::WString::fromUTF8("Удалить телефонный номер"));

    dialog->resize(600, 550);



	mysql_init(&mysql);
	conn=mysql_real_connect(&mysql, server, user, password, database, 0, 0, 0);
	/*
	if(conn==NULL)
	{
	    std::cout<<mysql_error(&mysql)<<std::endl<<std::endl;
	}
	 */
	mysql_query(&mysql,"SET NAMES 'UTF8'");



    Wt::WTreeTable *treeTable;
	treeTable = new Wt::WTreeTable(dialog->contents());
    //treeTable->resize(650, 300);
    treeTable->setStyleClass(Wt::WString::fromUTF8("Wt-treetable col-lg-12 col-md-12"));
    treeTable->tree()->setSelectionMode(Wt::SingleSelection);
    //treeTable->addColumn(Wt::WString::fromUTF8("Телефонные номера"), 100);

    Wt::WTreeTableNode *tree_root;
	tree_root = new Wt::WTreeTableNode(Wt::WString::fromUTF8("Номера"));
    treeTable->setTreeRoot(tree_root, Wt::WString::fromUTF8("Телефонные номера"));

    Wt::WTreeTableNode *tree_node;

    std::string mysql_get_numbers = "";

// add node form mysql table
	if (operation_name == "create")
	{
		mysql_get_numbers = "SELECT number FROM phone_numbers WHERE number_status = 'not_processed'";
	} else // operation_name == "edit"
	{
		mysql_get_numbers = "SELECT number FROM phone_numbers WHERE  subscriber_id = '"+subscriber_id_edit_mode+"'";
	}
	query_state=mysql_query(conn, mysql_get_numbers.c_str());
	if(query_state!=0)
	{
	   std::cout<<mysql_error(conn)<<std::endl<<std::endl;
	}
	res=mysql_store_result(conn);
	std::cout<<"MySQL Values in the amaDB Table.5"<<std::endl<<std::endl;
	while((row=mysql_fetch_row(res))!=NULL)
	{
		tree_node  = new Wt::WTreeTableNode(Wt::WString::fromUTF8(row[0]), 0, tree_root);
		//tree_node ->setColumnWidget(1, new Wt::WText(Wt::WString::fromUTF8(row[2])));
	}

	mysql_free_result(res);
	mysql_close(conn);

	tree_root->expand();



    Wt::WPushButton *ok = new Wt::WPushButton(Wt::WString::fromUTF8("Удалить"), dialog->footer());
    ok->setDefault(true);


    Wt::WPushButton *cancel = new Wt::WPushButton("Cancel", dialog->footer());
    dialog->rejectWhenEscapePressed();



    // Accept the dialog
    ok->clicked().connect(std::bind([=] () {
	    dialog->accept();
    }));


    // Reject the dialog
    cancel->clicked().connect(dialog, &Wt::WDialog::reject);


    // Process the dialog result.
    dialog->finished().connect(std::bind([=] () {
	if (dialog->result() == Wt::WDialog::Accepted)
	{


		mysql_init(&mysql);
		conn=mysql_real_connect(&mysql, server, user, password, database, 0, 0, 0);
		/*
		if(conn==NULL)
		{
		    std::cout<<mysql_error(&mysql)<<std::endl<<std::endl;
		}
		 */
		mysql_query(&mysql,"SET NAMES 'UTF8'");



		std::string mysql_delete_number = "";
		std::string selected_number = "";

		Wt::WTreeNode *selected_node; // operator* returns contents of an interator
		std::set<Wt::WTreeNode* > highlightedRows = treeTable->tree()->selectedNodes();
		if (!highlightedRows.empty())
		{
			for (std::set<Wt::WTreeNode* >::iterator i = highlightedRows.begin(); i != highlightedRows.end(); ++i)
			{
			  selected_node = *i;
			}

			selected_number = selected_node->label()->text().toUTF8();

			if (operation_name == "create")
			{
				mysql_delete_number = "DELETE FROM phone_numbers WHERE number = '"+selected_number+"'";
			} else // operation_name == "edit"
			{
				mysql_delete_number = "DELETE FROM phone_numbers WHERE number = '"+selected_number+"' AND subscriber_id = '"+subscriber_id_edit_mode+"'";
			}
			highlightedRows.clear();
		}


		query_state=mysql_query(conn, mysql_delete_number.c_str());

		if(query_state!=0)
		{
		   std::cout<<mysql_error(conn)<<std::endl<<std::endl;
		}



		phone_number_table->clear();
		phone_number_table->elementAt(0, 0)->addWidget(new Wt::WText(Wt::WString::fromUTF8("Номер")));
		phone_number_table->elementAt(0, 1)->addWidget(new Wt::WText(Wt::WString::fromUTF8("Устройство")));
		phone_number_table->elementAt(0, 2)->addWidget(new Wt::WText(Wt::WString::fromUTF8("С")));
		phone_number_table->elementAt(0, 3)->addWidget(new Wt::WText(Wt::WString::fromUTF8("По")));
		phone_number_table->elementAt(0, 4)->addWidget(new Wt::WText(Wt::WString::fromUTF8("Тарифный план")));
		phone_number_table->elementAt(0, 5)->addWidget(new Wt::WText(Wt::WString::fromUTF8("Описание")));

		int row_number = 0;


		std::string mysql_phone_number_table_data = "";

		if (operation_name == "create")
		{
			mysql_phone_number_table_data = "select device, number, description, date_since, date_by, "
					  "tariff_plan from phone_numbers where phone_numbers.number_status = 'not_processed'";
		} else // operation_name == "edit"
		{
			mysql_phone_number_table_data = "select device, number, description, date_since, date_by, "
					  "tariff_plan from phone_numbers where phone_numbers.subscriber_id = '"+subscriber_id_edit_mode+"'";
		}


		query_state=mysql_query(conn, mysql_phone_number_table_data.c_str());
		//query_state=mysql_query(conn, "select device, ip_address, description, date_since, date_by, "
		//							  "tariff_plan from ip_addresses where ip_addresses.ip_status = '"not_processed"'");
		if(query_state!=0)
		{
		   std::cout<<mysql_error(conn)<<std::endl<<std::endl;
		}
		res=mysql_store_result(conn);
		while((row=mysql_fetch_row(res))!=NULL)
		{
			row_number++;
			new Wt::WText(Wt::WString::fromUTF8(row[1]), phone_number_table->elementAt(row_number, 0));
			new Wt::WText(Wt::WString::fromUTF8(row[0]), phone_number_table->elementAt(row_number, 1));
			new Wt::WText(Wt::WString::fromUTF8(row[3]), phone_number_table->elementAt(row_number, 2));
			new Wt::WText(Wt::WString::fromUTF8(row[4]), phone_number_table->elementAt(row_number, 3));
			new Wt::WText(Wt::WString::fromUTF8(row[5]), phone_number_table->elementAt(row_number, 4));
			new Wt::WText(Wt::WString::fromUTF8(row[2]), phone_number_table->elementAt(row_number, 5));
		}
		phone_number_table->refresh();
		mysql_free_result(res);
		mysql_close(conn);
	}
	else
	{
	}

	delete dialog;
    }));

    dialog->show();
}





// show dialog window where you manage (create, delete, change etc) phone numbers
extern void WtAccounts::subscriber_phone_number_dialog(std::string operation_name)
{
    Wt::WDialog *dialog = new Wt::WDialog(Wt::WString::fromUTF8("Телефонные номера"));

    dialog->resize(1050, 450);



    // top buttons
    Wt::WPushButton *save_exit_button = new Wt::WPushButton(Wt::WString::fromUTF8("Сохранить и закрыть"), dialog->contents());
    save_exit_button->setStyleClass(Wt::WString::fromUTF8("btn btn-default with-label col-md-3 col-lg-3"));

    Wt::WPushButton *add_ip_button = new Wt::WPushButton(Wt::WString::fromUTF8("Добавить"), dialog->contents());
    add_ip_button->setStyleClass(Wt::WString::fromUTF8("btn btn-default with-label col-md-1 col-lg-1"));

    Wt::WPushButton *change_ip_button = new Wt::WPushButton(Wt::WString::fromUTF8("Изменить"), dialog->contents());
    change_ip_button->setStyleClass(Wt::WString::fromUTF8("btn btn-default with-label col-md-1 col-lg-1"));

    Wt::WPushButton *delete_ip_button = new Wt::WPushButton(Wt::WString::fromUTF8("Удалить"), dialog->contents());
    delete_ip_button->setStyleClass(Wt::WString::fromUTF8("btn btn-default with-label col-md-1 col-lg-1"));

    Wt::WPushButton *set_asmain_button = new Wt::WPushButton(Wt::WString::fromUTF8("Установить как основной"), dialog->contents());
    set_asmain_button->setStyleClass(Wt::WString::fromUTF8("btn btn-default with-label col-md-3 col-lg-3"));

    Wt::WPushButton *only_active_button = new Wt::WPushButton(Wt::WString::fromUTF8("Только активные"), dialog->contents());
    only_active_button->setStyleClass(Wt::WString::fromUTF8("btn btn-default with-label col-md-3 col-lg-3"));



	add_ip_button->clicked().connect(boost::bind(&WtAccounts::create_phone_number_dialog, this, operation_name));
	delete_ip_button->clicked().connect(boost::bind(&WtAccounts::delete_phone_number_dialog, this, operation_name));



	mysql_init(&mysql);
	conn=mysql_real_connect(&mysql, server, user, password, database, 0, 0, 0);
	/*
	if(conn==NULL)
	{
	    std::cout<<mysql_error(&mysql)<<std::endl<<std::endl;
	}
	 */
	mysql_query(&mysql,"SET NAMES 'UTF8'");



	// table with data about ip address
	phone_number_table = new Wt::WTable(dialog->contents());
	phone_number_table->setHeaderCount(1);
	phone_number_table->setWidth(Wt::WLength("100%"));

	phone_number_table->setHeaderCount(1);

	phone_number_table->elementAt(0, 0)->addWidget(new Wt::WText(Wt::WString::fromUTF8("Номер")));
	phone_number_table->elementAt(0, 1)->addWidget(new Wt::WText(Wt::WString::fromUTF8("Устройство")));
	phone_number_table->elementAt(0, 2)->addWidget(new Wt::WText(Wt::WString::fromUTF8("С")));
	phone_number_table->elementAt(0, 3)->addWidget(new Wt::WText(Wt::WString::fromUTF8("По")));
	phone_number_table->elementAt(0, 4)->addWidget(new Wt::WText(Wt::WString::fromUTF8("Тарифный план")));
	phone_number_table->elementAt(0, 5)->addWidget(new Wt::WText(Wt::WString::fromUTF8("Описание")));

	int row_number = 0;

	std::string mysql_phone_number_table_data = "";

	if (operation_name == "create")
	{
		mysql_phone_number_table_data = "select device, number, description, date_since, date_by, "
				  "tariff_plan from phone_numbers where phone_numbers.number_status = 'not_processed'";
	} else // operation_name == "edit"
	{
		mysql_phone_number_table_data = "select device, number, description, date_since, date_by, "
				  "tariff_plan from phone_numbers where phone_numbers.subscriber_id = '"+subscriber_id_edit_mode+"'";
	}

	query_state=mysql_query(conn, mysql_phone_number_table_data.c_str());
	//query_state=mysql_query(conn, "select device, ip_address, description, date_since, date_by, "
	//							  "tariff_plan from ip_addresses where ip_addresses.ip_status = '"not_processed"'");
	if(query_state!=0)
	{
	   std::cout<<mysql_error(conn)<<std::endl<<std::endl;
	}
	res=mysql_store_result(conn);
	while((row=mysql_fetch_row(res))!=NULL)
	{
		row_number++;
		new Wt::WText(Wt::WString::fromUTF8(row[1]), phone_number_table->elementAt(row_number, 0));
		new Wt::WText(Wt::WString::fromUTF8(row[0]), phone_number_table->elementAt(row_number, 1));
		new Wt::WText(Wt::WString::fromUTF8(row[3]), phone_number_table->elementAt(row_number, 2));
		new Wt::WText(Wt::WString::fromUTF8(row[4]), phone_number_table->elementAt(row_number, 3));
		new Wt::WText(Wt::WString::fromUTF8(row[5]), phone_number_table->elementAt(row_number, 4));
		new Wt::WText(Wt::WString::fromUTF8(row[2]), phone_number_table->elementAt(row_number, 5));
	}
	row_number = 0;
	phone_number_table->addStyleClass("table form-inline table-bordered table-hover table-condensed table-striped top_mar top_pad");


	mysql_free_result(res);
	mysql_close(conn);;



    dialog->contents()->addStyleClass("form-group");


    //Wt::WPushButton *ok = new Wt::WPushButton("OK", dialog->footer());
    //ok->setDefault(true);

    Wt::WPushButton *cancel = new Wt::WPushButton("Cancel", dialog->footer());
    dialog->rejectWhenEscapePressed();


    // Accept the dialog
    save_exit_button->clicked().connect(std::bind([=] () {
	    dialog->accept();
    }));


    // Reject the dialog
    cancel->clicked().connect(dialog, &Wt::WDialog::reject);


    // Process the dialog result.
    dialog->finished().connect(std::bind([=] () {
	if (dialog->result() == Wt::WDialog::Accepted)
	{
		mysql_init(&mysql);
		conn=mysql_real_connect(&mysql, server, user, password, database, 0, 0, 0);
		/*
		if(conn==NULL)
		{
		    std::cout<<mysql_error(&mysql)<<std::endl<<std::endl;
		}
		 */
		mysql_query(&mysql,"SET NAMES 'UTF8'");


		// click button save and exit get new ip addresses and write in ip address entry in main form
		std::string mysql_get_number = "";

		if (operation_name == "create")
		{
			mysql_get_number = "SELECT number FROM phone_numbers WHERE phone_numbers.number_status = 'not_processed'";
		} else // operation_name == "edit"
		{
			mysql_get_number = "SELECT number FROM phone_numbers WHERE phone_numbers.subscriber_id = '"+subscriber_id_edit_mode+"'";
		}


		query_state=mysql_query(conn, mysql_get_number.c_str());

		std::string new_phone_numbers = "";
		if(query_state!=0)
		{
		   std::cout<<mysql_error(conn)<<std::endl<<std::endl;
		}
		res=mysql_store_result(conn);
		row=mysql_fetch_row(res);
		while(row!=NULL)
		{
			new_phone_numbers.append(row[0]);
			row=mysql_fetch_row(res);
			if (row!=NULL)
			{
				new_phone_numbers.append(", ");
			}
		}
		mysql_free_result(res);
		mysql_close(conn);

		if (operation_name == "create")
		{
			ui->user_number_edit->setText(Wt::WString::fromUTF8(new_phone_numbers));
		} else // operation_name == "edit"
		{
			ui->user_number_edit_edit_user_tab->setText(Wt::WString::fromUTF8(new_phone_numbers));
		}
	}


	delete dialog;
    }));

    dialog->show();
}






// show dialog window where you create new ip addresses
extern void WtAccounts::create_ip_address_dialog(std::string operation_name)
{
    Wt::WDialog *dialog = new Wt::WDialog(Wt::WString::fromUTF8("Новый IP адрес"));

    dialog->resize(600, 550);

	mysql_init(&mysql);
	conn=mysql_real_connect(&mysql, server, user, password, database, 0, 0, 0);
	if(conn==NULL)
	{
	    std::cout<<mysql_error(&mysql)<<std::endl<<std::endl;
	}
	mysql_query(&mysql,"SET NAMES 'UTF8'");



    // device label and edit
    Wt::WLabel *device_label = new Wt::WLabel(Wt::WString::fromUTF8("Устройство"),
    				       dialog->contents());
    device_label->setStyleClass("col-lg-3 col-md-3 top_pad top_mar");

    Wt::WContainerWidget *device_edit_container = new Wt::WContainerWidget(dialog->contents());
    device_edit_container->setStyleClass(Wt::WString::fromUTF8("col-md-9 col-lg-9 top_mar"));
    device_edit_container->setHtmlTagName("div");

    Wt::WLineEdit *device_edit = new Wt::WLineEdit(device_edit_container);
    device_edit->setText(Wt::WString::fromUTF8("Netflow"));
    device_label->setBuddy(device_edit);



    // range label and combo box
    Wt::WLabel *range_label = new Wt::WLabel(Wt::WString::fromUTF8("Диапазон"),
    				       dialog->contents());
    range_label->setStyleClass("col-lg-3 col-md-3 top_pad top_mar");

    Wt::WContainerWidget *range_combobox_container = new Wt::WContainerWidget(dialog->contents());
    range_combobox_container->setStyleClass(Wt::WString::fromUTF8("col-md-9 col-lg-9 top_mar"));
    range_combobox_container->setHtmlTagName("div");

    Wt::WComboBox *range_combobox = new Wt::WComboBox(range_combobox_container);
    range_label->setBuddy(range_combobox);



    // ip label and edit
    Wt::WLabel *ip_label = new Wt::WLabel(Wt::WString::fromUTF8("IP"),
    				       dialog->contents());
    ip_label->setStyleClass("col-lg-3 col-md-3 top_pad top_mar");

    Wt::WContainerWidget *ip_edit_container = new Wt::WContainerWidget(dialog->contents());
    ip_edit_container->setStyleClass(Wt::WString::fromUTF8("col-md-9 col-lg-9 top_mar"));
    ip_edit_container->setHtmlTagName("div");

    Wt::WLineEdit *ip_edit = new Wt::WLineEdit(ip_edit_container);
    ip_label->setBuddy(ip_edit);



    // description label and text area
    Wt::WLabel *description_label = new Wt::WLabel(Wt::WString::fromUTF8("Описание"),
    				       dialog->contents());
    description_label->setStyleClass("col-lg-3 col-md-3 top_pad top_mar");

    Wt::WContainerWidget *description_text_area_container = new Wt::WContainerWidget(dialog->contents());
    description_text_area_container->setStyleClass(Wt::WString::fromUTF8("col-md-9 col-lg-9 top_mar"));
    description_text_area_container->setHtmlTagName("div");

    Wt::WTextArea *description_text_area = new Wt::WTextArea(description_text_area_container);
    description_text_area->setColumns(80);
    description_text_area->setRows(3);
    description_label->setBuddy(description_text_area);



    // include date label, check box and date edit
    Wt::WLabel *include_date_label = new Wt::WLabel(Wt::WString::fromUTF8("Включен с"),
    				       dialog->contents());
    include_date_label->setStyleClass("col-lg-3 col-md-3 top_pad top_mar");


    Wt::WCheckBox *include_date_checkbox = new Wt::WCheckBox("", dialog->contents());
    include_date_checkbox->setStyleClass("col-lg-1 col-md-1 top_pad");

    Wt::WContainerWidget *include_date_edit_container = new Wt::WContainerWidget(dialog->contents());
    include_date_edit_container->setStyleClass(Wt::WString::fromUTF8("col-md-8 col-lg-8 top_mar"));
    include_date_edit_container->setHtmlTagName("div");

    Wt::WDateEdit *include_date_edit = new Wt::WDateEdit(include_date_edit_container);
    include_date_edit->setFormat("yyyy-MM-dd");
    include_date_label->setBuddy(include_date_edit);



    // disable date label, check box and date edit
    Wt::WLabel *disable_date_label = new Wt::WLabel(Wt::WString::fromUTF8("По"),
    				       dialog->contents());
    disable_date_label->setStyleClass("col-lg-3 col-md-3 top_pad top_mar");


    Wt::WCheckBox *disable_date_checkbox = new Wt::WCheckBox("", dialog->contents());
    disable_date_checkbox->setStyleClass("col-lg-1 col-md-1 top_pad");

    Wt::WContainerWidget *disable_date_edit_container = new Wt::WContainerWidget(dialog->contents());
    disable_date_edit_container->setStyleClass(Wt::WString::fromUTF8("col-md-8 col-lg-8 top_mar"));
    disable_date_edit_container->setHtmlTagName("div");

    Wt::WDateEdit *disable_date_edit = new Wt::WDateEdit(disable_date_edit_container);
    disable_date_edit->setFormat("yyyy-MM-dd");
    disable_date_label->setBuddy(disable_date_edit);



    // tariff plan label and combo box
    Wt::WLabel *tariff_plan_label = new Wt::WLabel(Wt::WString::fromUTF8("Тарифный план"),
    				       dialog->contents());
    tariff_plan_label->setStyleClass("col-lg-3 col-md-3 top_pad");

    Wt::WContainerWidget *tariff_plan_combobox_container = new Wt::WContainerWidget(dialog->contents());
    tariff_plan_combobox_container->setStyleClass(Wt::WString::fromUTF8("col-md-9 col-lg-9 top_mar"));
    tariff_plan_combobox_container->setHtmlTagName("div");

    Wt::WComboBox *tariff_plan_combobox = new Wt::WComboBox(tariff_plan_combobox_container);
    tariff_plan_label->setBuddy(tariff_plan_combobox);

    query_state=mysql_query(conn, "SELECT plan_name FROM tariff_plan");

	if(query_state!=0)
	{
	   std::cout<<mysql_error(conn)<<std::endl<<std::endl;
	}
	res=mysql_store_result(conn);
	while((row=mysql_fetch_row(res))!=NULL)
	{
		tariff_plan_combobox->addItem(Wt::WString::fromUTF8(row[0]));
	}

	mysql_free_result(res);
	mysql_close(conn);





    dialog->contents()->addStyleClass("form-group");


    Wt::WPushButton *ok = new Wt::WPushButton("OK", dialog->footer());
    ok->setDefault(true);


    Wt::WPushButton *cancel = new Wt::WPushButton("Cancel", dialog->footer());
    dialog->rejectWhenEscapePressed();



    // Accept the dialog
    ok->clicked().connect(std::bind([=] () {
	    dialog->accept();
    }));


    // Reject the dialog
    cancel->clicked().connect(dialog, &Wt::WDialog::reject);


    // Process the dialog result.
    dialog->finished().connect(std::bind([=] () {
	if (dialog->result() == Wt::WDialog::Accepted)
	{


		mysql_init(&mysql);
		conn=mysql_real_connect(&mysql, server, user, password, database, 0, 0, 0);
		if(conn==NULL)
		{
		    std::cout<<mysql_error(&mysql)<<std::endl<<std::endl;
		}
		mysql_query(&mysql,"SET NAMES 'UTF8'");


		std::string device = device_edit->text().toUTF8();
		std::string ip_address = ip_edit->text().toUTF8();
		std::string description = description_text_area->text().toUTF8();

		std::string date_since = "";
		if (include_date_checkbox->isChecked())
		{
			date_since = boost::lexical_cast<std::string>(include_date_edit->text());
		}

		std::string date_by = "";
		if (disable_date_checkbox->isChecked())
		{
			date_by = boost::lexical_cast<std::string>(disable_date_edit->text());
		}

		std::string tariff_plan = tariff_plan_combobox->currentText().toUTF8();

		std::string mysql_insert_new_ip = "";



		if (operation_name == "create")
		{
			mysql_insert_new_ip = "insert into ip_addresses (subscriber_id, device, ip_address, "
							"description, date_since, date_by, tariff_plan, ip_status)  "
							"values (NULL, '"+device+"', '"+ip_address+"', "
									"'"+description+"', '"+date_since+"', '"+date_by+"', '"+tariff_plan+"', 'not_processed')";
		} else // operation_name == "edit"
		{
			mysql_insert_new_ip = "insert into ip_addresses (subscriber_id, device, ip_address, "
							"description, date_since, date_by, tariff_plan, ip_status)  "
							"values ('"+subscriber_id_edit_mode+"', '"+device+"', '"+ip_address+"', "
									"'"+description+"', '"+date_since+"', '"+date_by+"', '"+tariff_plan+"', 'processed')";
		}

		query_state=mysql_query(conn, mysql_insert_new_ip.c_str());
		//query_state=mysql_query(conn, "select device, ip_address, description, date_since, date_by, "
		//							  "tariff_plan from ip_addresses where ip_addresses.ip_status = '"not_processed"'");
		if(query_state!=0)
		{
		   std::cout<<mysql_error(conn)<<std::endl<<std::endl;
		}


		ip_address_table->clear();
		ip_address_table->elementAt(0, 0)->addWidget(new Wt::WText(Wt::WString::fromUTF8("IP адрес")));
		ip_address_table->elementAt(0, 1)->addWidget(new Wt::WText(Wt::WString::fromUTF8("Устройство")));
		ip_address_table->elementAt(0, 2)->addWidget(new Wt::WText(Wt::WString::fromUTF8("С")));
		ip_address_table->elementAt(0, 3)->addWidget(new Wt::WText(Wt::WString::fromUTF8("По")));
		ip_address_table->elementAt(0, 4)->addWidget(new Wt::WText(Wt::WString::fromUTF8("Тарифный план")));
		ip_address_table->elementAt(0, 5)->addWidget(new Wt::WText(Wt::WString::fromUTF8("Описание")));

		int row_number = 0;


		std::string mysql_ip_address_table_data = "";

		if (operation_name == "create")
		{
			mysql_ip_address_table_data = "select device, ip_address, description, date_since, date_by, "
					  "tariff_plan from ip_addresses where ip_addresses.ip_status = 'not_processed'";
		} else // operation_name == "edit"
		{
			mysql_ip_address_table_data = "select device, ip_address, description, date_since, date_by, "
					  "tariff_plan from ip_addresses where ip_addresses.subscriber_id = '"+subscriber_id_edit_mode+"'";
		}


		query_state=mysql_query(conn, mysql_ip_address_table_data.c_str());
		//query_state=mysql_query(conn, "select device, ip_address, description, date_since, date_by, "
		//							  "tariff_plan from ip_addresses where ip_addresses.ip_status = '"not_processed"'");
		if(query_state!=0)
		{
		   std::cout<<mysql_error(conn)<<std::endl<<std::endl;
		}
		res=mysql_store_result(conn);
		while((row=mysql_fetch_row(res))!=NULL)
		{
			row_number++;
			new Wt::WText(Wt::WString::fromUTF8(row[1]), ip_address_table->elementAt(row_number, 0));
			new Wt::WText(Wt::WString::fromUTF8(row[0]), ip_address_table->elementAt(row_number, 1));
			new Wt::WText(Wt::WString::fromUTF8(row[3]), ip_address_table->elementAt(row_number, 2));
			new Wt::WText(Wt::WString::fromUTF8(row[4]), ip_address_table->elementAt(row_number, 3));
			new Wt::WText(Wt::WString::fromUTF8(row[5]), ip_address_table->elementAt(row_number, 4));
			new Wt::WText(Wt::WString::fromUTF8(row[2]), ip_address_table->elementAt(row_number, 5));
		}
		ip_address_table->refresh();
		mysql_free_result(res);
		mysql_close(conn);
	}
	else
	{
	}

	delete dialog;
    }));

    dialog->show();
}





// show dialog window where you delete exist ip addresses
extern void WtAccounts::delete_ip_address_dialog(std::string operation_name)
{
    Wt::WDialog *dialog = new Wt::WDialog(Wt::WString::fromUTF8("Удалить IP адресс"));

    dialog->resize(600, 550);



	mysql_init(&mysql);
	conn=mysql_real_connect(&mysql, server, user, password, database, 0, 0, 0);
	/*
	if(conn==NULL)
	{
	    std::cout<<mysql_error(&mysql)<<std::endl<<std::endl;
	}
	 */
	mysql_query(&mysql,"SET NAMES 'UTF8'");



    Wt::WTreeTable *treeTable;
	treeTable = new Wt::WTreeTable(dialog->contents());
    //treeTable->resize(650, 300);
    treeTable->setStyleClass(Wt::WString::fromUTF8("Wt-treetable col-lg-12 col-md-12"));
    treeTable->tree()->setSelectionMode(Wt::SingleSelection);
    //treeTable->addColumn(Wt::WString::fromUTF8("Телефонные номера"), 100);

    Wt::WTreeTableNode *tree_root;
	tree_root = new Wt::WTreeTableNode(Wt::WString::fromUTF8("Адреса"));
    treeTable->setTreeRoot(tree_root, Wt::WString::fromUTF8("IP адреса"));

    Wt::WTreeTableNode *tree_node;

    std::string mysql_get_ip_addresses = "";

// add node form mysql table
	if (operation_name == "create")
	{
		mysql_get_ip_addresses = "SELECT ip_address FROM ip_addresses WHERE ip_status = 'not_processed'";
	} else // operation_name == "edit"
	{
		mysql_get_ip_addresses = "SELECT ip_address FROM ip_addresses WHERE  subscriber_id = '"+subscriber_id_edit_mode+"'";
	}
	query_state=mysql_query(conn, mysql_get_ip_addresses.c_str());
	if(query_state!=0)
	{
	   std::cout<<mysql_error(conn)<<std::endl<<std::endl;
	}
	res=mysql_store_result(conn);
	std::cout<<"MySQL Values in the amaDB Table.6"<<std::endl<<std::endl;
	while((row=mysql_fetch_row(res))!=NULL)
	{
		tree_node  = new Wt::WTreeTableNode(Wt::WString::fromUTF8(row[0]), 0, tree_root);
		//tree_node ->setColumnWidget(1, new Wt::WText(Wt::WString::fromUTF8(row[2])));
	}

	mysql_free_result(res);
	mysql_close(conn);

	tree_root->expand();



    Wt::WPushButton *ok = new Wt::WPushButton(Wt::WString::fromUTF8("Удалить"), dialog->footer());
    ok->setDefault(true);


    Wt::WPushButton *cancel = new Wt::WPushButton("Cancel", dialog->footer());
    dialog->rejectWhenEscapePressed();



    // Accept the dialog
    ok->clicked().connect(std::bind([=] () {
	    dialog->accept();
    }));


    // Reject the dialog
    cancel->clicked().connect(dialog, &Wt::WDialog::reject);


    // Process the dialog result.
    dialog->finished().connect(std::bind([=] () {
	if (dialog->result() == Wt::WDialog::Accepted)
	{


		mysql_init(&mysql);
		conn=mysql_real_connect(&mysql, server, user, password, database, 0, 0, 0);
		/*
		if(conn==NULL)
		{
		    std::cout<<mysql_error(&mysql)<<std::endl<<std::endl;
		}
		 */
		mysql_query(&mysql,"SET NAMES 'UTF8'");



		std::string mysql_delete_ip_address = "";
		std::string selected_ip_address = "";

		Wt::WTreeNode *selected_node; // operator* returns contents of an interator
		std::set<Wt::WTreeNode* > highlightedRows = treeTable->tree()->selectedNodes();
		if (!highlightedRows.empty())
		{
			for (std::set<Wt::WTreeNode* >::iterator i = highlightedRows.begin(); i != highlightedRows.end(); ++i)
			{
			  selected_node = *i;
			}

			selected_ip_address= selected_node->label()->text().toUTF8();

			if (operation_name == "create")
			{
				mysql_delete_ip_address = "DELETE FROM ip_addresses WHERE ip_address = '"+selected_ip_address+"'";
			} else // operation_name == "edit"
			{
				mysql_delete_ip_address = "DELETE FROM ip_addresses WHERE ip_address = '"+selected_ip_address+"' AND subscriber_id = '"+subscriber_id_edit_mode+"'";
			}
			highlightedRows.clear();
		}


		query_state=mysql_query(conn, mysql_delete_ip_address.c_str());

		if(query_state!=0)
		{
		   std::cout<<mysql_error(conn)<<std::endl<<std::endl;
		}



		ip_address_table->clear();
		ip_address_table->elementAt(0, 0)->addWidget(new Wt::WText(Wt::WString::fromUTF8("IP адрес")));
		ip_address_table->elementAt(0, 1)->addWidget(new Wt::WText(Wt::WString::fromUTF8("Устройство")));
		ip_address_table->elementAt(0, 2)->addWidget(new Wt::WText(Wt::WString::fromUTF8("С")));
		ip_address_table->elementAt(0, 3)->addWidget(new Wt::WText(Wt::WString::fromUTF8("По")));
		ip_address_table->elementAt(0, 4)->addWidget(new Wt::WText(Wt::WString::fromUTF8("Тарифный план")));
		ip_address_table->elementAt(0, 5)->addWidget(new Wt::WText(Wt::WString::fromUTF8("Описание")));

		int row_number = 0;


		std::string mysql_ip_addresses_table_data = "";

		if (operation_name == "create")
		{
			mysql_ip_addresses_table_data = "select device, ip_address, description, date_since, date_by, "
					  "tariff_plan from ip_addresses where ip_addresses.ip_status = 'not_processed'";
		} else // operation_name == "edit"
		{
			mysql_ip_addresses_table_data = "select device, ip_address, description, date_since, date_by, "
					  "tariff_plan from ip_addresses where ip_addresses.subscriber_id = '"+subscriber_id_edit_mode+"'";
		}


		query_state=mysql_query(conn, mysql_ip_addresses_table_data.c_str());
		//query_state=mysql_query(conn, "select device, ip_address, description, date_since, date_by, "
		//							  "tariff_plan from ip_addresses where ip_addresses.ip_status = '"not_processed"'");
		if(query_state!=0)
		{
		   std::cout<<mysql_error(conn)<<std::endl<<std::endl;
		}
		res=mysql_store_result(conn);
		while((row=mysql_fetch_row(res))!=NULL)
		{
			row_number++;
			new Wt::WText(Wt::WString::fromUTF8(row[1]), ip_address_table->elementAt(row_number, 0));
			new Wt::WText(Wt::WString::fromUTF8(row[0]), ip_address_table->elementAt(row_number, 1));
			new Wt::WText(Wt::WString::fromUTF8(row[3]), ip_address_table->elementAt(row_number, 2));
			new Wt::WText(Wt::WString::fromUTF8(row[4]), ip_address_table->elementAt(row_number, 3));
			new Wt::WText(Wt::WString::fromUTF8(row[5]), ip_address_table->elementAt(row_number, 4));
			new Wt::WText(Wt::WString::fromUTF8(row[2]), ip_address_table->elementAt(row_number, 5));
		}
		ip_address_table->refresh();
		mysql_free_result(res);
		mysql_close(conn);
	}
	else
	{
	}

	delete dialog;
    }));

    dialog->show();
}





// show dialog window where you manage (create, delete, change etc) subscriber ip addresses
extern void WtAccounts::subscriber_ip_address_dialog(std::string operation_name)
{
    Wt::WDialog *dialog = new Wt::WDialog(Wt::WString::fromUTF8("IP адреса"));

    dialog->resize(1050, 450);



    // top buttons
    Wt::WPushButton *save_exit_button = new Wt::WPushButton(Wt::WString::fromUTF8("Сохранить и закрыть"), dialog->contents());
    save_exit_button->setStyleClass(Wt::WString::fromUTF8("btn btn-default with-label col-md-3 col-lg-3"));

    Wt::WPushButton *add_ip_button = new Wt::WPushButton(Wt::WString::fromUTF8("Добавить"), dialog->contents());
    add_ip_button->setStyleClass(Wt::WString::fromUTF8("btn btn-default with-label col-md-1 col-lg-1"));

    Wt::WPushButton *change_ip_button = new Wt::WPushButton(Wt::WString::fromUTF8("Изменить"), dialog->contents());
    change_ip_button->setStyleClass(Wt::WString::fromUTF8("btn btn-default with-label col-md-1 col-lg-1"));

    Wt::WPushButton *delete_ip_button = new Wt::WPushButton(Wt::WString::fromUTF8("Удалить"), dialog->contents());
    delete_ip_button->setStyleClass(Wt::WString::fromUTF8("btn btn-default with-label col-md-1 col-lg-1"));

    Wt::WPushButton *set_asmain_button = new Wt::WPushButton(Wt::WString::fromUTF8("Установить как основной"), dialog->contents());
    set_asmain_button->setStyleClass(Wt::WString::fromUTF8("btn btn-default with-label col-md-3 col-lg-3"));

    Wt::WPushButton *only_active_button = new Wt::WPushButton(Wt::WString::fromUTF8("Только активные"), dialog->contents());
    only_active_button->setStyleClass(Wt::WString::fromUTF8("btn btn-default with-label col-md-3 col-lg-3"));


	add_ip_button->clicked().connect(boost::bind(&WtAccounts::create_ip_address_dialog, this, operation_name));
	delete_ip_button->clicked().connect(boost::bind(&WtAccounts::delete_ip_address_dialog, this, operation_name));






	mysql_init(&mysql);
	conn=mysql_real_connect(&mysql, server, user, password, database, 0, 0, 0);
	if(conn==NULL)
	{
	    std::cout<<mysql_error(&mysql)<<std::endl<<std::endl;
	}
	mysql_query(&mysql,"SET NAMES 'UTF8'");




	// table with data about ip address
	ip_address_table = new Wt::WTable(dialog->contents());
	ip_address_table->setHeaderCount(1);
	ip_address_table->setWidth(Wt::WLength("100%"));

	ip_address_table->setHeaderCount(1);

	ip_address_table->elementAt(0, 0)->addWidget(new Wt::WText(Wt::WString::fromUTF8("IP адрес")));
	ip_address_table->elementAt(0, 1)->addWidget(new Wt::WText(Wt::WString::fromUTF8("Устройство")));
	ip_address_table->elementAt(0, 2)->addWidget(new Wt::WText(Wt::WString::fromUTF8("С")));
	ip_address_table->elementAt(0, 3)->addWidget(new Wt::WText(Wt::WString::fromUTF8("По")));
	ip_address_table->elementAt(0, 4)->addWidget(new Wt::WText(Wt::WString::fromUTF8("Тарифный план")));
	ip_address_table->elementAt(0, 5)->addWidget(new Wt::WText(Wt::WString::fromUTF8("Описание")));

	int row_number = 0;



	std::string mysql_ip_address_table_data = "";

	if (operation_name == "create")
	{
		mysql_ip_address_table_data = "select device, ip_address, description, date_since, date_by, "
				  "tariff_plan from ip_addresses where ip_addresses.ip_status = 'not_processed'";
	} else // operation_name == "edit"
	{
		mysql_ip_address_table_data = "select device, ip_address, description, date_since, date_by, "
				  "tariff_plan from ip_addresses where ip_addresses.subscriber_id = '"+subscriber_id_edit_mode+"'";
	}

	query_state=mysql_query(conn, mysql_ip_address_table_data.c_str());
	//query_state=mysql_query(conn, "select device, ip_address, description, date_since, date_by, "
	//							  "tariff_plan from ip_addresses where ip_addresses.ip_status = '"not_processed"'");
	if(query_state!=0)
	{
	   std::cout<<mysql_error(conn)<<std::endl<<std::endl;
	}
	res=mysql_store_result(conn);
	while((row=mysql_fetch_row(res))!=NULL)
	{
		row_number++;
		new Wt::WText(Wt::WString::fromUTF8(row[1]), ip_address_table->elementAt(row_number, 0));
		new Wt::WText(Wt::WString::fromUTF8(row[0]), ip_address_table->elementAt(row_number, 1));
		new Wt::WText(Wt::WString::fromUTF8(row[3]), ip_address_table->elementAt(row_number, 2));
		new Wt::WText(Wt::WString::fromUTF8(row[4]), ip_address_table->elementAt(row_number, 3));
		new Wt::WText(Wt::WString::fromUTF8(row[5]), ip_address_table->elementAt(row_number, 4));
		new Wt::WText(Wt::WString::fromUTF8(row[2]), ip_address_table->elementAt(row_number, 5));
	}
	row_number = 0;
	ip_address_table->addStyleClass("table form-inline table-bordered table-hover table-condensed table-striped top_mar top_pad");


	mysql_free_result(res);
	mysql_close(conn);;




    dialog->contents()->addStyleClass("form-group");



    //Wt::WPushButton *ok = new Wt::WPushButton("OK", dialog->footer());
    //ok->setDefault(true);


    Wt::WPushButton *cancel = new Wt::WPushButton("Cancel", dialog->footer());
    dialog->rejectWhenEscapePressed();



    // Accept the dialog
    save_exit_button->clicked().connect(std::bind([=] () {
	    dialog->accept();
    }));


    // Reject the dialog
    cancel->clicked().connect(dialog, &Wt::WDialog::reject);


    // Process the dialog result.
    dialog->finished().connect(std::bind([=] () {
	if (dialog->result() == Wt::WDialog::Accepted)
	{
		mysql_init(&mysql);
		conn=mysql_real_connect(&mysql, server, user, password, database, 0, 0, 0);
		/*
		if(conn==NULL)
		{
		    std::cout<<mysql_error(&mysql)<<std::endl<<std::endl;
		}
		 */
		mysql_query(&mysql,"SET NAMES 'UTF8'");


		// click button save and exit get new ip addresses and write in ip address entry in main form
		std::string mysql_get_ip_address = "";

		if (operation_name == "create")
		{
			mysql_get_ip_address = "SELECT ip_address FROM ip_addresses WHERE ip_addresses.ip_status = 'not_processed'";
		} else // operation_name == "edit"
		{
			mysql_get_ip_address = "SELECT ip_address FROM ip_addresses WHERE ip_addresses.subscriber_id = '"+subscriber_id_edit_mode+"'";
		}


		query_state=mysql_query(conn, mysql_get_ip_address.c_str());

		std::string new_ip_addresses = "";
		if(query_state!=0)
		{
		   std::cout<<mysql_error(conn)<<std::endl<<std::endl;
		}
		res=mysql_store_result(conn);
		row=mysql_fetch_row(res);
		while(row!=NULL)
		{
			new_ip_addresses.append(row[0]);
			row=mysql_fetch_row(res);
			if (row!=NULL)
			{
				new_ip_addresses.append(", ");
			}
		}
		mysql_free_result(res);
		mysql_close(conn);
		if (operation_name == "create")
		{
			ui->ip_login_edit->setText(Wt::WString::fromUTF8(new_ip_addresses));
		} else // operation_name == "edit"
		{
			ui->ip_login_edit_edit_user_tab->setText(Wt::WString::fromUTF8(new_ip_addresses));
		}
	}
	else
	{
	}

	delete dialog;
    }));

    dialog->show();
}





// show dialog window where you can chose tariff plan
extern void WtAccounts::subscriber_tariff_plan_dialog(std::string operation_name)
{
	mysql_init(&mysql);
	conn=mysql_real_connect(&mysql, server, user, password, database, 0, 0, 0);
	if(conn==NULL)
	{
	    std::cout<<mysql_error(&mysql)<<std::endl<<std::endl;
	}
	 mysql_query(&mysql,"SET NAMES 'UTF8'");



    Wt::WDialog *dialog = new Wt::WDialog(Wt::WString::fromUTF8("Выберите тарифный план абонента:"));

    dialog->resize(500, 450);

// dialog contents
    Wt::WTreeTable *treeTable;
	treeTable = new Wt::WTreeTable(dialog->contents());
    //treeTable->resize(650, 300);
    treeTable->setStyleClass(Wt::WString::fromUTF8("Wt-treetable col-lg-12 col-md-12"));
    treeTable->tree()->setSelectionMode(Wt::SingleSelection);
    //treeTable->addColumn(Wt::WString::fromUTF8("Абонентов"), 100);


    Wt::WTreeTableNode *tree_root;
	tree_root = new Wt::WTreeTableNode(Wt::WString::fromUTF8("Тарифные планы"));
    treeTable->setTreeRoot(tree_root, Wt::WString::fromUTF8("Тарифы"));

    Wt::WTreeTableNode *tree_node;



// add node form mysql table
	query_state=mysql_query(conn, "select * from tariff_plan");
	if(query_state!=0)
	{
	   std::cout<<mysql_error(conn)<<std::endl<<std::endl;
	}
	res=mysql_store_result(conn);
	std::cout<<"MySQL Values in the amaDB Table.7"<<std::endl<<std::endl;
	while((row=mysql_fetch_row(res))!=NULL)
	{
		tree_node  = new Wt::WTreeTableNode(Wt::WString::fromUTF8(row[1]), 0, tree_root);
		//tree_node ->setColumnWidget(1, new Wt::WText(Wt::WString::fromUTF8(row[2])));
	}


	mysql_free_result(res);
	mysql_close(conn);

	tree_root->expand();



// dialog footer
    Wt::WPushButton *ok = new Wt::WPushButton("OK", dialog->footer());
    ok->setDefault(true);


    Wt::WPushButton *cancel = new Wt::WPushButton("Cancel", dialog->footer());
    dialog->rejectWhenEscapePressed();


    /*
     * Accept the dialog
     */
    ok->clicked().connect(std::bind([=] () {
	    dialog->accept();
    }));

    /*
     * Reject the dialog
     */
    cancel->clicked().connect(dialog, &Wt::WDialog::reject);

    /*
     * Process the dialog result.
     */
    dialog->finished().connect(std::bind([=] () {
	if (dialog->result() == Wt::WDialog::Accepted)
	{
		Wt::WTreeNode *selected_node; // operator* returns contents of an interator
		std::set<Wt::WTreeNode* > highlightedRows = treeTable->tree()->selectedNodes();
		if (!highlightedRows.empty())
		{
			for (std::set<Wt::WTreeNode* >::iterator i = highlightedRows.begin(); i != highlightedRows.end(); ++i)
			{
			  selected_node = *i;
			}
			if (operation_name == "create")
			{
				ui->tariff_plan_edit->setText(selected_node->label()->text());
				tariff_plan = selected_node->label()->text().toUTF8();
			} else // operation_name == "edit"
			{
				ui->tariff_plan_edit_edit_user_tab->setText(selected_node->label()->text());
				tariff_plan_edit_mode = selected_node->label()->text().toUTF8();
			}
			highlightedRows.clear();
		}
	}

	delete dialog;
    }));


    dialog->show();
}





// show dialog window where fill subscriber address information or change
extern void WtAccounts::subscriber_contact_dialog(std::string operation_name)
{
    Wt::WDialog *dialog = new Wt::WDialog(Wt::WString::fromUTF8("Адресс"));

    dialog->resize(650, 400);



// city edit and label
    Wt::WLabel *city_label = new Wt::WLabel(Wt::WString::fromUTF8("Город"),
				       dialog->contents());
    city_label->setStyleClass("col-lg-2 col-md-2 top_pad");

    Wt::WContainerWidget *city_edit_container = new Wt::WContainerWidget(dialog->contents());
    city_edit_container->setStyleClass(Wt::WString::fromUTF8("col-md-4 col-lg-4"));
    city_edit_container->setHtmlTagName("div");

    Wt::WLineEdit *city_edit = new Wt::WLineEdit(city_edit_container);
    city_label->setBuddy(city_edit);



// index_number edit and label
     Wt::WLabel *index_number_label = new Wt::WLabel(Wt::WString::fromUTF8("Индекс"),
    				       dialog->contents());
     index_number_label->setStyleClass("col-lg-2 col-md-2 top_mar top_pad");

     Wt::WContainerWidget *index_number_edit_container = new Wt::WContainerWidget(dialog->contents());
     index_number_edit_container->setStyleClass(Wt::WString::fromUTF8("col-md-4 col-lg-4 top_mar"));
     index_number_edit_container->setHtmlTagName("div");
     Wt::WLineEdit *index_number_edit = new Wt::WLineEdit(index_number_edit_container);
     index_number_label->setBuddy(index_number_edit);



// district edit and label
    Wt::WLabel *district_label = new Wt::WLabel(Wt::WString::fromUTF8("Район"),
				       dialog->contents());
    district_label->setStyleClass("col-lg-2 col-md-2 top_mar top_pad");

    Wt::WContainerWidget *district_edit_container = new Wt::WContainerWidget(dialog->contents());
    district_edit_container->setStyleClass(Wt::WString::fromUTF8("col-md-10 col-lg-10 top_mar"));
    district_edit_container->setHtmlTagName("div");
    Wt::WLineEdit *district_edit = new Wt::WLineEdit(district_edit_container);
    district_label->setBuddy(district_edit);



// street edit and label
    Wt::WLabel *street_label = new Wt::WLabel(Wt::WString::fromUTF8("Улица"),
				       dialog->contents());
    street_label->setStyleClass("col-lg-2 col-md-2 top_mar top_pad");

    Wt::WContainerWidget *street_edit_container = new Wt::WContainerWidget(dialog->contents());
    street_edit_container->setStyleClass(Wt::WString::fromUTF8("col-md-10 col-lg-10 top_mar"));
    street_edit_container->setHtmlTagName("div");
    Wt::WLineEdit *street_edit = new Wt::WLineEdit(street_edit_container);
    street_label->setBuddy(street_edit);



// housing edit and label
    Wt::WLabel *housing_label = new Wt::WLabel(Wt::WString::fromUTF8("Корпус"),
				       dialog->contents());
    housing_label->setStyleClass("col-lg-2 col-md-2 top_mar top_pad");

    Wt::WContainerWidget *housing_edit_container = new Wt::WContainerWidget(dialog->contents());
    housing_edit_container->setStyleClass(Wt::WString::fromUTF8("col-md-4 col-lg-4 top_mar"));
    housing_edit_container->setHtmlTagName("div");
    Wt::WLineEdit *housing_edit = new Wt::WLineEdit(housing_edit_container);
    housing_label->setBuddy(housing_edit);



// house edit and label
     Wt::WLabel *house_label = new Wt::WLabel(Wt::WString::fromUTF8("Дом"),
    				       dialog->contents());
     house_label->setStyleClass("col-lg-2 col-md-2 top_mar top_pad");

     Wt::WContainerWidget *house_edit_container = new Wt::WContainerWidget(dialog->contents());
     house_edit_container->setStyleClass(Wt::WString::fromUTF8("col-md-4 col-lg-4 top_mar"));
     house_edit_container->setHtmlTagName("div");
     Wt::WLineEdit *house_edit = new Wt::WLineEdit(house_edit_container);
     house_label->setBuddy(house_edit);



// floor edit and label
    Wt::WLabel *floor_label = new Wt::WLabel(Wt::WString::fromUTF8("Этаж"),
				       dialog->contents());
    floor_label->setStyleClass("col-lg-2 col-md-2 top_mar top_pad");

    Wt::WContainerWidget *floor_edit_container = new Wt::WContainerWidget(dialog->contents());
    floor_edit_container->setStyleClass(Wt::WString::fromUTF8("col-md-4 col-lg-4 top_mar"));
    floor_edit_container->setHtmlTagName("div");
    Wt::WLineEdit *floor_edit = new Wt::WLineEdit(floor_edit_container);
    floor_label->setBuddy(floor_edit);



// apartment edit and label
    Wt::WLabel *apartment_label = new Wt::WLabel(Wt::WString::fromUTF8("Квартира"),
				       dialog->contents());
    apartment_label->setStyleClass("col-lg-2 col-md-2 top_mar top_pad");

    Wt::WContainerWidget *apartment_edit_container = new Wt::WContainerWidget(dialog->contents());
    apartment_edit_container->setStyleClass(Wt::WString::fromUTF8("col-md-4 col-lg-4 top_mar"));
    apartment_edit_container->setHtmlTagName("div");
    Wt::WLineEdit *apartment_edit = new Wt::WLineEdit(apartment_edit_container);
    apartment_label->setBuddy(apartment_edit);


    // if edit mode thwn we fill dialog window's entries with contact data about subscriber
    if (operation_name == "edit")
    {
    	    city_edit->setText(Wt::WString::fromUTF8(city_edit_mode));
    	    index_number_edit->setText(Wt::WString::fromUTF8(index_number_edit_mode));
    	    district_edit->setText(Wt::WString::fromUTF8(district_edit_mode));
    	    street_edit->setText(Wt::WString::fromUTF8(street_edit_mode));
    	    housing_edit->setText(Wt::WString::fromUTF8(housing_edit_mode));
    	    house_edit->setText(Wt::WString::fromUTF8(house_edit_mode));
    	    floor_edit->setText(Wt::WString::fromUTF8(house_floor_edit_mode));
    	    apartment_edit->setText(Wt::WString::fromUTF8(apartment_edit_mode));

    }


    dialog->contents()->addStyleClass("form-group");



    /*
    Wt::WRegExpValidator *validator =
        new Wt::WRegExpValidator("[A-Za-z][1-9][0-9]{0,2}");
    validator->setMandatory(true);
    edit->setValidator(validator);
     */
    Wt::WPushButton *ok = new Wt::WPushButton("OK", dialog->footer());
    ok->setDefault(true);
    //if (wApp->environment().ajax())
     // ok->disable();

    Wt::WPushButton *cancel = new Wt::WPushButton("Cancel", dialog->footer());
    dialog->rejectWhenEscapePressed();

    /*edit->keyWentUp().connect(std::bind([=] () {
	ok->setDisabled(edit->validate() != Wt::WValidator::Valid);
    }));*/

    /*
     * Accept the dialog
     */
    ok->clicked().connect(std::bind([=] () {
	//if (edit->validate())
	    dialog->accept();
    }));

    /*
     * Reject the dialog
     */
    cancel->clicked().connect(dialog, &Wt::WDialog::reject);

    /*
     * Process the dialog result.
     */
    dialog->finished().connect(std::bind([=] () {
	if (dialog->result() == Wt::WDialog::Accepted)
	{
		if (operation_name == "create")
		{
			city = city_edit->text().toUTF8();
			district = district_edit->text().toUTF8();
			street = street_edit->text().toUTF8();
			housing = housing_edit->text().toUTF8();
			house_floor = floor_edit->text().toUTF8();
			house = house_edit->text().toUTF8();
			apartment = apartment_edit->text().toUTF8();
			index_number = index_number_edit->text().toUTF8();

			ui->user_address_text_area->setText(Wt::WString::fromUTF8("Город: ") + city_edit->text() + "\n" + Wt::WString::fromUTF8("Район: ") + district_edit->text() + "\n" +
					Wt::WString::fromUTF8("Улица: ") + street_edit->text() + "\n" + Wt::WString::fromUTF8("Корпус: ") + housing_edit->text() + "\n" + Wt::WString::fromUTF8("Этаж:") + floor_edit->text() + "\n" +
					Wt::WString::fromUTF8("Дом: ") + house_edit->text() + "\n" + Wt::WString::fromUTF8("Квартира: ") + apartment_edit->text() + "\n" + Wt::WString::fromUTF8("Индекс: ") + index_number_edit->text());
		} else
		{
			if (city_edit->text() != "") city_edit_mode = city_edit->text().toUTF8();
			if (district_edit->text() != "") district_edit_mode = district_edit->text().toUTF8();
			if (street_edit->text() != "") street_edit_mode = street_edit->text().toUTF8();
			if (housing_edit->text() != "") housing_edit_mode = housing_edit->text().toUTF8();
			if (floor_edit->text() != "") house_floor_edit_mode = floor_edit->text().toUTF8();
			if (house_edit->text() != "") house_edit_mode = house_edit->text().toUTF8();
			if (apartment_edit->text() != "") apartment_edit_mode = apartment_edit->text().toUTF8();
			if (index_number_edit->text() != "") index_number_edit_mode = index_number_edit->text().toUTF8();

			ui->user_address_text_area_edit_user_tab->setText(Wt::WString::fromUTF8("Город: ") + Wt::WString::fromUTF8(city_edit_mode) + "\n" + Wt::WString::fromUTF8("Район: ") + Wt::WString::fromUTF8(district_edit_mode) + "\n" +
					Wt::WString::fromUTF8("Улица: ") + Wt::WString::fromUTF8(street_edit_mode) + "\n" + Wt::WString::fromUTF8("Корпус: ") + Wt::WString::fromUTF8(housing_edit_mode) + "\n" + Wt::WString::fromUTF8("Этаж:") + Wt::WString::fromUTF8(house_floor_edit_mode) + "\n" +
					Wt::WString::fromUTF8("Дом: ") + Wt::WString::fromUTF8(house_edit_mode) + "\n" + Wt::WString::fromUTF8("Квартира: ") + Wt::WString::fromUTF8(apartment_edit_mode) + "\n" + Wt::WString::fromUTF8("Индекс: ") + Wt::WString::fromUTF8(index_number_edit_mode));
		}

	}

	delete dialog;
    }));

    dialog->show();
}





// subscriber services &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
// ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
// show dialog window where you add subscriber services
extern void WtAccounts::add_service_dialog(std::string operation_name)
{
    Wt::WDialog *dialog = new Wt::WDialog(Wt::WString::fromUTF8("Абонентская услуга"));

    dialog->resize(700, 750);

	mysql_init(&mysql);
	conn=mysql_real_connect(&mysql, server, user, password, database, 0, 0, 0);
	if(conn==NULL)
	{
	    std::cout<<mysql_error(&mysql)<<std::endl<<std::endl;
	}
	mysql_query(&mysql,"SET NAMES 'UTF8'");



// dialog contents
    Wt::WTreeTable *treeTable;
	treeTable = new Wt::WTreeTable(dialog->contents());
    treeTable->resize(650, 300);
    //treeTable->setStyleClass(Wt::WString::fromUTF8("Wt-treetable col-lg-12 col-md-12"));
    treeTable->setStyleClass(Wt::WString::fromUTF8("Wt-treetable"));
    treeTable->tree()->setSelectionMode(Wt::SingleSelection);
    treeTable->addColumn(Wt::WString::fromUTF8("Стоимость"), 100);


    Wt::WTreeTableNode *tree_root;
	tree_root = new Wt::WTreeTableNode(Wt::WString::fromUTF8("Абонентские услуги"));
    treeTable->setTreeRoot(tree_root, Wt::WString::fromUTF8("Названия"));

    Wt::WTreeTableNode *tree_node;



// add node form mysql table
	query_state=mysql_query(conn, "SELECT * FROM subscriber_services WHERE charging_period <> 'Ручное начисление'");
	if(query_state!=0)
	{
	   std::cout<<mysql_error(conn)<<std::endl<<std::endl;
	}
	res=mysql_store_result(conn);
	std::cout<<"MySQL Values in the amaDB Table.8"<<std::endl<<std::endl;
	while((row=mysql_fetch_row(res))!=NULL)
	{
		tree_node  = new Wt::WTreeTableNode(Wt::WString::fromUTF8(row[1]), 0, tree_root);
		tree_node ->setColumnWidget(1, new Wt::WText(Wt::WString::fromUTF8(row[7])));
	}


	mysql_free_result(res);

	tree_root->expand();



    // quantity label and edit
    Wt::WLabel *amount_label = new Wt::WLabel(Wt::WString::fromUTF8("Количество:"),
    				       dialog->contents());
    amount_label->setStyleClass("col-lg-3 col-md-3 top_pad top_mar");

    Wt::WContainerWidget *amount_edit_container = new Wt::WContainerWidget(dialog->contents());
    amount_edit_container->setStyleClass(Wt::WString::fromUTF8("col-md-9 col-lg-9 top_mar"));
    amount_edit_container->setHtmlTagName("div");

    Wt::WLineEdit *amount_edit = new Wt::WLineEdit(amount_edit_container);
    amount_edit->setText(Wt::WString::fromUTF8("1"));
    amount_label->setBuddy(amount_edit);



    // number/ip label and combo box
    Wt::WLabel *number_ip_label = new Wt::WLabel(Wt::WString::fromUTF8("Номер/IP:"),
    				       dialog->contents());
    number_ip_label->setStyleClass("col-lg-3 col-md-3 top_pad top_mar");

    Wt::WContainerWidget *number_ip_combobox_container = new Wt::WContainerWidget(dialog->contents());
    number_ip_combobox_container->setStyleClass(Wt::WString::fromUTF8("col-md-9 col-lg-9 top_mar"));
    number_ip_combobox_container->setHtmlTagName("div");

    Wt::WComboBox *number_ip_combobox = new Wt::WComboBox(number_ip_combobox_container);
    number_ip_label->setBuddy(number_ip_combobox);

    std::string mysql_get_number_ip = "";
    if (operation_name == "create") {
    	mysql_get_number_ip = "SELECT ip_address FROM ip_addresses "
    			"WHERE ip_addresses.ip_status = 'not_processed'";
		query_state=mysql_query(conn, mysql_get_number_ip.c_str());

		if(query_state!=0)
		{
		   std::cout<<mysql_error(conn)<<std::endl<<std::endl;
		}
		res=mysql_store_result(conn);

		number_ip_combobox->addItem(Wt::WString::fromUTF8(" ")); // if we don't set IP or phone number

		while((row=mysql_fetch_row(res))!=NULL)
		{
			number_ip_combobox->addItem(Wt::WString::fromUTF8(row[0]));
		}

		mysql_get_number_ip = "SELECT number FROM phone_numbers "
				"WHERE phone_numbers.number_status = 'not_processed'";
		query_state=mysql_query(conn, mysql_get_number_ip.c_str());
		if(query_state!=0)
		{
		   std::cout<<mysql_error(conn)<<std::endl<<std::endl;
		}
		res=mysql_store_result(conn);
		while((row=mysql_fetch_row(res))!=NULL)
		{
			number_ip_combobox->addItem(Wt::WString::fromUTF8(row[0]));
		}
    } else { // operation_name == "edit"

    	mysql_get_number_ip = "SELECT ip_address FROM ip_addresses "
    			"WHERE ip_addresses.subscriber_id = '"+ subscriber_id_edit_mode +"'";
		query_state=mysql_query(conn, mysql_get_number_ip.c_str());
		if(query_state!=0)
		{
		   std::cout<<mysql_error(conn)<<std::endl<<std::endl;
		}
		res=mysql_store_result(conn);
		while((row=mysql_fetch_row(res))!=NULL)
		{
			number_ip_combobox->addItem(Wt::WString::fromUTF8(row[0]));
		}

    	mysql_get_number_ip = "SELECT number FROM phone_numbers "
    			"WHERE phone_numbers.subscriber_id = '"+ subscriber_id_edit_mode +"'";
		query_state=mysql_query(conn, mysql_get_number_ip.c_str());
		if(query_state!=0)
		{
		   std::cout<<mysql_error(conn)<<std::endl<<std::endl;
		}
		res=mysql_store_result(conn);

		number_ip_combobox->addItem(Wt::WString::fromUTF8(" ")); // if we don't set IP or phone number

		while((row=mysql_fetch_row(res))!=NULL)
		{
			number_ip_combobox->addItem(Wt::WString::fromUTF8(row[0]));
		}
    }



    // description label and text area
    Wt::WLabel *description_label = new Wt::WLabel(Wt::WString::fromUTF8("Описание:"),
    				       dialog->contents());
    description_label->setStyleClass("col-lg-3 col-md-3 top_pad top_mar");

    Wt::WContainerWidget *description_text_area_container = new Wt::WContainerWidget(dialog->contents());
    description_text_area_container->setStyleClass(Wt::WString::fromUTF8("col-md-9 col-lg-9 top_mar"));
    description_text_area_container->setHtmlTagName("div");

    Wt::WTextArea *description_text_area = new Wt::WTextArea(description_text_area_container);
    description_text_area->setColumns(80);
    description_text_area->setRows(3);
    description_label->setBuddy(description_text_area);



    // include date label, check box and date edit
    Wt::WLabel *include_date_label = new Wt::WLabel(Wt::WString::fromUTF8("С:"),
    				       dialog->contents());
    include_date_label->setStyleClass("col-lg-3 col-md-3 top_pad top_mar");


    Wt::WCheckBox *include_date_checkbox = new Wt::WCheckBox("", dialog->contents());
    include_date_checkbox->setStyleClass("col-lg-1 col-md-1 top_pad");

    Wt::WContainerWidget *include_date_edit_container = new Wt::WContainerWidget(dialog->contents());
    include_date_edit_container->setStyleClass(Wt::WString::fromUTF8("col-md-8 col-lg-8 top_mar"));
    include_date_edit_container->setHtmlTagName("div");

    Wt::WDateEdit *include_date_edit = new Wt::WDateEdit(include_date_edit_container);
    include_date_edit->setFormat("yyyy-MM-dd");
    include_date_label->setBuddy(include_date_edit);



    // disable date label, check box and date edit
    Wt::WLabel *disable_date_label = new Wt::WLabel(Wt::WString::fromUTF8("По:"),
    				       dialog->contents());
    disable_date_label->setStyleClass("col-lg-3 col-md-3 top_pad top_mar");


    Wt::WCheckBox *disable_date_checkbox = new Wt::WCheckBox("", dialog->contents());
    disable_date_checkbox->setStyleClass("col-lg-1 col-md-1 top_pad");

    Wt::WContainerWidget *disable_date_edit_container = new Wt::WContainerWidget(dialog->contents());
    disable_date_edit_container->setStyleClass(Wt::WString::fromUTF8("col-md-8 col-lg-8 top_mar"));
    disable_date_edit_container->setHtmlTagName("div");

    Wt::WDateEdit *disable_date_edit = new Wt::WDateEdit(disable_date_edit_container);
    disable_date_edit->setFormat("yyyy-MM-dd");
    disable_date_label->setBuddy(disable_date_edit);



	mysql_free_result(res);
	mysql_close(conn);



    dialog->contents()->addStyleClass("form-group");


    Wt::WPushButton *ok = new Wt::WPushButton("OK", dialog->footer());
    ok->setDefault(true);


    Wt::WPushButton *cancel = new Wt::WPushButton("Cancel", dialog->footer());
    dialog->rejectWhenEscapePressed();



    // Accept the dialog
    ok->clicked().connect(std::bind([=] () {
	    dialog->accept();
    }));


    // Reject the dialog
    cancel->clicked().connect(dialog, &Wt::WDialog::reject);


    // Process the dialog result.
    dialog->finished().connect(std::bind([=] () {
	if (dialog->result() == Wt::WDialog::Accepted)
	{

		std::string service_name = "";
		std::string amount = "";
		std::string number_ip = "";
		std::string description = "";
		std::string date_since = "";
		std::string date_by = "";



		Wt::WTreeNode *selected_node; // operator* returns contents of an interator
		std::set<Wt::WTreeNode* > highlightedRows = treeTable->tree()->selectedNodes();
		if (!highlightedRows.empty())
		{
			for (std::set<Wt::WTreeNode* >::iterator i = highlightedRows.begin(); i != highlightedRows.end(); ++i)
			{
			  selected_node = *i;
			}
			service_name = selected_node->label()->text().toUTF8();
			highlightedRows.clear();
		}



		mysql_init(&mysql);
		conn=mysql_real_connect(&mysql, server, user, password, database, 0, 0, 0);
		if(conn==NULL)
		{
		    std::cout<<mysql_error(&mysql)<<std::endl<<std::endl;
		}
		mysql_query(&mysql,"SET NAMES 'UTF8'");



		amount = amount_edit->text().toUTF8();
		number_ip = number_ip_combobox->currentText().toUTF8();
		description = description_text_area->text().toUTF8();

		if (include_date_checkbox->isChecked())
		{
			date_since= boost::lexical_cast<std::string>(include_date_edit->text());
		}

		if (disable_date_checkbox->isChecked())
		{
			date_by = boost::lexical_cast<std::string>(disable_date_edit->text());
		}

		std::string mysql_insert_add_service = "";



		if (operation_name == "create")
		{
			mysql_insert_add_service = "INSERT INTO subscriber_connected_services "
					"(subscriber_id, service_id, service, quantity, number_ip, "
					"description, date_since, date_by, service_status, charging_period) "
					"values (NULL, NULL, '"+ service_name +"', '"+ amount +"', "
					"'"+ number_ip +"', '"+ description +"', '"+ date_since +"', "
					"'"+ date_by +"', 'not_processed', '')";
		} else // operation_name == "edit"
		{
			mysql_insert_add_service =  "INSERT INTO subscriber_connected_services "
					"(subscriber_id, service_id, service, quantity, number_ip, "
					"description, date_since, date_by, service_status, charging_period)  "
					"values ('"+subscriber_id_edit_mode+"', NULL, '"+ service_name +"', "
					"'"+ amount +"', '"+ number_ip +"', '"+ description +"', "
					"'"+ date_since +"', '"+ date_by +"', 'processed', '')";
		}

		query_state=mysql_query(conn, mysql_insert_add_service.c_str());
		if(query_state!=0)
		{
		   std::cout<<mysql_error(conn)<<std::endl<<std::endl;
		}


		subscriber_connected_table->clear();
		subscriber_connected_table->elementAt(0, 0)->addWidget(new Wt::WText(Wt::WString::fromUTF8("Услуга")));
		subscriber_connected_table->elementAt(0, 1)->addWidget(new Wt::WText(Wt::WString::fromUTF8("Номер/IP")));
		subscriber_connected_table->elementAt(0, 2)->addWidget(new Wt::WText(Wt::WString::fromUTF8("С")));
		subscriber_connected_table->elementAt(0, 3)->addWidget(new Wt::WText(Wt::WString::fromUTF8("По")));
		subscriber_connected_table->elementAt(0, 4)->addWidget(new Wt::WText(Wt::WString::fromUTF8("Количество")));
		subscriber_connected_table->elementAt(0, 5)->addWidget(new Wt::WText(Wt::WString::fromUTF8("Описание")));

		int row_number = 0;



		std::string mysql_service_table_data = "";

		if (operation_name == "create")
		{
			mysql_service_table_data = "select service, quantity, number_ip, description, date_since, date_by "
					  "from subscriber_connected_services where subscriber_connected_services.service_status = 'not_processed'";
		} else // operation_name == "edit"
		{
			mysql_service_table_data = "select service, quantity, number_ip, description, date_since, date_by "
					  "from subscriber_connected_services where subscriber_connected_services.subscriber_id = '"+subscriber_id_edit_mode+"'";
		}

		query_state=mysql_query(conn, mysql_service_table_data.c_str());
		if(query_state!=0)
		{
		   std::cout<<mysql_error(conn)<<std::endl<<std::endl;
		}
		res=mysql_store_result(conn);
		while((row=mysql_fetch_row(res))!=NULL)
		{
			row_number++;
			new Wt::WText(Wt::WString::fromUTF8(row[0]), subscriber_connected_table->elementAt(row_number, 0));
			new Wt::WText(Wt::WString::fromUTF8(row[2]), subscriber_connected_table->elementAt(row_number, 1));
			new Wt::WText(Wt::WString::fromUTF8(row[4]), subscriber_connected_table->elementAt(row_number, 2));
			new Wt::WText(Wt::WString::fromUTF8(row[5]), subscriber_connected_table->elementAt(row_number, 3));
			new Wt::WText(Wt::WString::fromUTF8(row[1]), subscriber_connected_table->elementAt(row_number, 4));
			new Wt::WText(Wt::WString::fromUTF8(row[3]), subscriber_connected_table->elementAt(row_number, 5));
		}
		subscriber_connected_table->refresh();
		mysql_free_result(res);
		mysql_close(conn);
	}
	else
	{
	}

	delete dialog;
    }));

    dialog->show();
}





// show dialog window where you delete subscriber services
extern void WtAccounts::delete_service_dialog(std::string operation_name)
{
    Wt::WDialog *dialog = new Wt::WDialog(Wt::WString::fromUTF8("Удалить Абонентскую Услугу"));

    dialog->resize(600, 550);



	mysql_init(&mysql);
	conn=mysql_real_connect(&mysql, server, user, password, database, 0, 0, 0);
	/*
	if(conn==NULL)
	{
	    std::cout<<mysql_error(&mysql)<<std::endl<<std::endl;
	}
	 */
	mysql_query(&mysql,"SET NAMES 'UTF8'");



    Wt::WTreeTable *treeTable;
	treeTable = new Wt::WTreeTable(dialog->contents());
    //treeTable->resize(650, 300);
    treeTable->setStyleClass(Wt::WString::fromUTF8("Wt-treetable col-lg-12 col-md-12"));
    treeTable->tree()->setSelectionMode(Wt::SingleSelection);
    treeTable->addColumn(Wt::WString::fromUTF8("Номер/IP"), 100);
    //treeTable->addColumn(Wt::WString::fromUTF8("Фикс. сумма"), 100);

    Wt::WTreeTableNode *tree_root;
	tree_root = new Wt::WTreeTableNode(Wt::WString::fromUTF8("Абонентские услуги"));
    treeTable->setTreeRoot(tree_root, Wt::WString::fromUTF8("Названия"));

    Wt::WTreeTableNode *tree_node;

    std::string mysql_get_ip_addresses = "";

// add node form mysql table
	if (operation_name == "create")
	{
		mysql_get_ip_addresses = "SELECT service, number_ip FROM subscriber_connected_services "
				"WHERE service_status = 'not_processed'";
	} else // operation_name == "edit"
	{
		mysql_get_ip_addresses = "SELECT service, number_ip FROM subscriber_connected_services "
				"WHERE  subscriber_id = '"+subscriber_id_edit_mode+"'";
	}
	query_state=mysql_query(conn, mysql_get_ip_addresses.c_str());
	if(query_state!=0)
	{
	   std::cout<<mysql_error(conn)<<std::endl<<std::endl;
	}
	res=mysql_store_result(conn);
	std::cout<<"MySQL Values in the amaDB Table.9"<<std::endl<<std::endl;
	while((row=mysql_fetch_row(res))!=NULL)
	{
		tree_node  = new Wt::WTreeTableNode(Wt::WString::fromUTF8(row[0]), 0, tree_root);
		tree_node ->setColumnWidget(1, new Wt::WText(Wt::WString::fromUTF8(row[1])));
		//tree_node ->setColumnWidget(2, new Wt::WText(Wt::WString::fromUTF8(row[2])));
	}

	mysql_free_result(res);
	mysql_close(conn);

	tree_root->expand();



    Wt::WPushButton *ok = new Wt::WPushButton(Wt::WString::fromUTF8("Удалить"), dialog->footer());
    ok->setDefault(true);


    Wt::WPushButton *cancel = new Wt::WPushButton("Cancel", dialog->footer());
    dialog->rejectWhenEscapePressed();



    // Accept the dialog
    ok->clicked().connect(std::bind([=] () {
	    dialog->accept();
    }));


    // Reject the dialog
    cancel->clicked().connect(dialog, &Wt::WDialog::reject);


    // Process the dialog result.
    dialog->finished().connect(std::bind([=] () {
	if (dialog->result() == Wt::WDialog::Accepted)
	{


		mysql_init(&mysql);
		conn=mysql_real_connect(&mysql, server, user, password, database, 0, 0, 0);
		/*
		if(conn==NULL)
		{
		    std::cout<<mysql_error(&mysql)<<std::endl<<std::endl;
		}
		 */
		mysql_query(&mysql,"SET NAMES 'UTF8'");



		std::string mysql_delete_ip_address = "";
		std::string selected_service = "";

		Wt::WTreeNode *selected_node; // operator* returns contents of an interator
		std::set<Wt::WTreeNode* > highlightedRows = treeTable->tree()->selectedNodes();
		if (!highlightedRows.empty())
		{
			for (std::set<Wt::WTreeNode* >::iterator i = highlightedRows.begin(); i != highlightedRows.end(); ++i)
			{
			  selected_node = *i;
			}

			selected_service= selected_node->label()->text().toUTF8();

			if (operation_name == "create")
			{
				mysql_delete_ip_address = "DELETE FROM subscriber_connected_services "
						"WHERE service = '"+selected_service+"'";
			} else // operation_name == "edit"
			{
				mysql_delete_ip_address = "DELETE FROM subscriber_connected_services "
						"WHERE service = '"+selected_service+"' "
						"AND subscriber_id = '"+subscriber_id_edit_mode+"'";
			}
			highlightedRows.clear();
		}


		query_state=mysql_query(conn, mysql_delete_ip_address.c_str());

		if(query_state!=0)
		{
		   std::cout<<mysql_error(conn)<<std::endl<<std::endl;
		}



		subscriber_connected_table->clear();
		subscriber_connected_table->elementAt(0, 0)->addWidget(new Wt::WText(Wt::WString::fromUTF8("Услуга")));
		subscriber_connected_table->elementAt(0, 1)->addWidget(new Wt::WText(Wt::WString::fromUTF8("Номер/IP")));
		subscriber_connected_table->elementAt(0, 2)->addWidget(new Wt::WText(Wt::WString::fromUTF8("С")));
		subscriber_connected_table->elementAt(0, 3)->addWidget(new Wt::WText(Wt::WString::fromUTF8("По")));
		subscriber_connected_table->elementAt(0, 4)->addWidget(new Wt::WText(Wt::WString::fromUTF8("Количество")));
		subscriber_connected_table->elementAt(0, 5)->addWidget(new Wt::WText(Wt::WString::fromUTF8("Описание")));

		int row_number = 0;



		std::string mysql_service_table_data = "";

		if (operation_name == "create")
		{
			mysql_service_table_data = "select service, quantity, number_ip, description, date_since, date_by "
					  "from subscriber_connected_services where subscriber_connected_services.service_status = 'not_processed'";
		} else // operation_name == "edit"
		{
			mysql_service_table_data = "select service, quantity, number_ip, description, date_since, date_by "
					  "from subscriber_connected_services where subscriber_connected_services.subscriber_id = '"+subscriber_id_edit_mode+"'";
		}

		query_state=mysql_query(conn, mysql_service_table_data.c_str());
		if(query_state!=0)
		{
		   std::cout<<mysql_error(conn)<<std::endl<<std::endl;
		}
		res=mysql_store_result(conn);
		while((row=mysql_fetch_row(res))!=NULL)
		{
			row_number++;
			new Wt::WText(Wt::WString::fromUTF8(row[0]), subscriber_connected_table->elementAt(row_number, 0));
			new Wt::WText(Wt::WString::fromUTF8(row[2]), subscriber_connected_table->elementAt(row_number, 1));
			new Wt::WText(Wt::WString::fromUTF8(row[4]), subscriber_connected_table->elementAt(row_number, 2));
			new Wt::WText(Wt::WString::fromUTF8(row[5]), subscriber_connected_table->elementAt(row_number, 3));
			new Wt::WText(Wt::WString::fromUTF8(row[1]), subscriber_connected_table->elementAt(row_number, 4));
			new Wt::WText(Wt::WString::fromUTF8(row[3]), subscriber_connected_table->elementAt(row_number, 5));
		}
		subscriber_connected_table->refresh();
		mysql_free_result(res);
		mysql_close(conn);
	}
	else
	{
	}

	delete dialog;
    }));

    dialog->show();
}





// !!!!!!!!! important !!!!!!!!!
// in create tab for button save and exit write code that handle 'not_processed' entries
// show dialog window where you manage (add, delete etc) subscriber services
extern void WtAccounts::subscriber_service_dialog(std::string operation_name)
{
    Wt::WDialog *dialog = new Wt::WDialog(Wt::WString::fromUTF8("Абонентские Услуги"));

    dialog->resize(1050, 450);



    // srevice top buttons
    Wt::WPushButton *save_exit_button = new Wt::WPushButton(Wt::WString::fromUTF8("Сохранить и закрыть"), dialog->contents());
    save_exit_button->setStyleClass(Wt::WString::fromUTF8("btn btn-default with-label col-md-3 col-lg-3"));

    Wt::WPushButton *add_service_button = new Wt::WPushButton(Wt::WString::fromUTF8("Добавить"), dialog->contents());
    add_service_button->setStyleClass(Wt::WString::fromUTF8("btn btn-default with-label col-md-3 col-lg-3"));

    //Wt::WPushButton *change_ip_button = new Wt::WPushButton(Wt::WString::fromUTF8("Изменить"), dialog->contents());
    //change_ip_button->setStyleClass(Wt::WString::fromUTF8("btn btn-default with-label col-md-1 col-lg-1"));

    Wt::WPushButton *delete_service_button = new Wt::WPushButton(Wt::WString::fromUTF8("Удалить"), dialog->contents());
    delete_service_button->setStyleClass(Wt::WString::fromUTF8("btn btn-default with-label col-md-3 col-lg-3"));


	add_service_button->clicked().connect(boost::bind(&WtAccounts::add_service_dialog, this, operation_name));
	delete_service_button->clicked().connect(boost::bind(&WtAccounts::delete_service_dialog, this, operation_name));



	mysql_init(&mysql);
	conn=mysql_real_connect(&mysql, server, user, password, database, 0, 0, 0);
	if(conn==NULL)
	{
	    std::cout<<mysql_error(&mysql)<<std::endl<<std::endl;
	}
	mysql_query(&mysql,"SET NAMES 'UTF8'");




	// table with data about ip address
	subscriber_connected_table = new Wt::WTable(dialog->contents());
	subscriber_connected_table->setHeaderCount(1);
	subscriber_connected_table->setWidth(Wt::WLength("100%"));

	subscriber_connected_table->setHeaderCount(1);

	subscriber_connected_table->elementAt(0, 0)->addWidget(new Wt::WText(Wt::WString::fromUTF8("Услуга")));
	subscriber_connected_table->elementAt(0, 1)->addWidget(new Wt::WText(Wt::WString::fromUTF8("Номер/IP")));
	subscriber_connected_table->elementAt(0, 2)->addWidget(new Wt::WText(Wt::WString::fromUTF8("С")));
	subscriber_connected_table->elementAt(0, 3)->addWidget(new Wt::WText(Wt::WString::fromUTF8("По")));
	subscriber_connected_table->elementAt(0, 4)->addWidget(new Wt::WText(Wt::WString::fromUTF8("Количество")));
	subscriber_connected_table->elementAt(0, 5)->addWidget(new Wt::WText(Wt::WString::fromUTF8("Описание")));

	int row_number = 0;



	std::string mysql_subscriber_service_table_data = "";

	if (operation_name == "create")
	{
		mysql_subscriber_service_table_data = "SELECT service, quantity, number_ip, description, date_since, date_by "
				  "FROM subscriber_connected_services WHERE service_status = 'not_processed'";
	} else // operation_name == "edit"
	{
		mysql_subscriber_service_table_data = "SELECT service, quantity, number_ip, description, date_since, date_by "
				  "FROM subscriber_connected_services WHERE subscriber_id = '"+ subscriber_id_edit_mode +"'";
	}

	query_state=mysql_query(conn, mysql_subscriber_service_table_data.c_str());
	if(query_state!=0)
	{
	   std::cout<<mysql_error(conn)<<std::endl<<std::endl;
	}
	res=mysql_store_result(conn);
	while((row=mysql_fetch_row(res))!=NULL)
	{
		row_number++;
		new Wt::WText(Wt::WString::fromUTF8(row[0]), subscriber_connected_table->elementAt(row_number, 0));
		new Wt::WText(Wt::WString::fromUTF8(row[2]), subscriber_connected_table->elementAt(row_number, 1));
		new Wt::WText(Wt::WString::fromUTF8(row[4]), subscriber_connected_table->elementAt(row_number, 2));
		new Wt::WText(Wt::WString::fromUTF8(row[5]), subscriber_connected_table->elementAt(row_number, 3));
		new Wt::WText(Wt::WString::fromUTF8(row[1]), subscriber_connected_table->elementAt(row_number, 4));
		new Wt::WText(Wt::WString::fromUTF8(row[3]), subscriber_connected_table->elementAt(row_number, 5));
	}
	row_number = 0;
	subscriber_connected_table->addStyleClass("table form-inline table-bordered table-hover table-condensed table-striped top_mar top_pad");


	mysql_free_result(res);
	mysql_close(conn);;



    dialog->contents()->addStyleClass("form-group");



    //Wt::WPushButton *ok = new Wt::WPushButton("OK", dialog->footer());
    //ok->setDefault(true);


    Wt::WPushButton *cancel = new Wt::WPushButton("Cancel", dialog->footer());
    dialog->rejectWhenEscapePressed();



    // Accept the dialog
    save_exit_button->clicked().connect(std::bind([=] () {
	    dialog->accept();
    }));


    // Reject the dialog
    cancel->clicked().connect(dialog, &Wt::WDialog::reject);


    // Process the dialog result.
    dialog->finished().connect(std::bind([=] () {
	if (dialog->result() == Wt::WDialog::Accepted)
	{
	}
	else
	{
	}

	delete dialog;
    }));

    dialog->show();
}

// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&





// tabs' top button functions
// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^





// save data from all entries in tab (operation_name determine what tab it's) and close this tab





extern void WtAccounts::save_data_and_close_tab(std::string operation_name)
{
	if (operation_name == "create")
	{
		try {
		mysql_init(&mysql);
		conn=mysql_real_connect(&mysql, server, user, password, database, 0, 0, 0);
		if(conn==NULL)
		{
			std::cout<<mysql_error(&mysql)<<std::endl<<std::endl;
		}
		mysql_query(&mysql,"SET NAMES 'UTF8'");
		if(conn==NULL)
		{
			std::cout<<mysql_error(&mysql)<<std::endl<<std::endl;
		}

// get group id through group name
		if(!group_name.empty())
		{
			mysql_query_str = "select group_id from subscriber_group where group_name = '"+group_name+"'";
			query_state=mysql_query(conn, mysql_query_str.c_str());
			if(query_state!=0)
			{
			   std::cout<<mysql_error(conn)<<std::endl<<std::endl;
			}
			res=mysql_store_result(conn);
			std::cout<<"MySQL Values in the amaDB Table.10"<<std::endl<<std::endl;
			row=mysql_fetch_row(res);
			group_id = boost::lexical_cast<std::string>(row[0]);
			mysql_free_result(res);

					mysql_query_str = "UPDATE subscriber_group SET subscribers_number_ingroup = subscribers_number_ingroup + 1 WHERE group_id = '"+group_id+"'";
					query_state=mysql_query(conn, mysql_query_str.c_str());
					if(query_state!=0)
					{
					   std::cout<<mysql_error(conn)<<std::endl<<std::endl;
					}
		}


	// get main subscriber info and write in mysql table
		//group_id = "1";
		//Wt::WString temp =ui->user_full_name_edit->text().toUTF8();
		full_name = ui->user_full_name_edit->text().toUTF8();
		//full_name = boost::locale::conv::utf_to_utf<std::string>(ui->user_full_name_edit->text());
		subscriber_type = ui->user_type_combo_box->currentText().toUTF8();
		account_number = ui->account_number_edit->text().narrow();
		user_login = ui->user_login_edit->text().toUTF8();
		user_password = ui->user_pass_edit->text().toUTF8();
		tariff_plan = ui->tariff_plan_edit->text().toUTF8();
		user_email = ui->user_email_edit->text().narrow();

		if (ui->user_include_date_checkbox->isChecked())
		{
			ui->user_include_date_date_edit->setFormat("yyyy-MM-dd");
			date_since = boost::lexical_cast<std::string>(ui->user_include_date_date_edit->text());
		}


		if (ui->user_disable_date_checkbox->isChecked())
		{
			ui->user_disable_date_date_edit->setFormat("yyyy-MM-dd");
			date_by = boost::lexical_cast<std::string>(ui->user_disable_date_date_edit->text());
		}



		std::cout << "Creat user init" << "***************************************************" << std::endl;



		std::string mysql_subscriber = "INSERT INTO subscriber (group_id, name, surname, patronymic, "
				"full_name, subscriber_type, account_number, user_login, user_password,"
				"date_since, date_by, tariff_plan, user_email) "
				"values ('"+group_id+"', '"+name+"','"+surname+"', '"+patronymic+"',"
				"'"+full_name+"', '"+subscriber_type+"','"+account_number+"', '"+user_login+"',"
				"'"+user_password+"', '"+date_since+"','"+date_by+"', '"+tariff_plan+"','"+user_email+"')";
		query_state=mysql_query(conn, mysql_subscriber.c_str());

		// get new subscriber id
		query_state=mysql_query(conn, "select LAST_INSERT_ID() from subscriber");

		res=mysql_store_result(conn);
		std::cout<<"Last insert ID in the amaDB table."<<std::endl<<std::endl;
		//row=mysql_fetch_row(res);
		//std::cout<<mysql_fetch_row(res)[0]<<std::endl<<std::endl;
		subscriber_id = boost::lexical_cast<std::string>(mysql_fetch_row(res)[0]);


		//std::cout << "Adilbek Cool " << subscriber_id << std::endl;
		//std::cout << "Adilbek Cool" << "***************************************************" << std::endl;

		// update subscriber_id in ip_addresses table (it's because when we create ip we don't now id of current subscriber) and change ip_satus on "processed"
		std::string mysql_ip_adreess_subscriber_id = "UPDATE ip_addresses SET subscriber_id = '"+subscriber_id+"', ip_status = 'processed' WHERE ip_addresses.ip_status = 'not_processed'";
		query_state=mysql_query(conn, mysql_ip_adreess_subscriber_id.c_str());

		if(query_state!=0)
		{
		   std::cout<<mysql_error(conn)<<std::endl<<std::endl;
		}



		// update subscriber_id in phone_numbers table (it's because when we create phone number we don't now id of current subscriber) and change number_satus on "processed"
		std::string mysql_phone_number_subscriber_id = "UPDATE phone_numbers SET subscriber_id = '"+subscriber_id+"', number_status = 'processed' WHERE phone_numbers.number_status = 'not_processed'";
		query_state=mysql_query(conn, mysql_phone_number_subscriber_id.c_str());

		if(query_state!=0)
		{
			  std::cout<<mysql_error(conn)<<std::endl<<std::endl;
		}



		// update subscriber_id in subscriber_connected_services table (it's because when we add service to subscriber we don't now id of current subscriber) and change service_status on "processed"
		std::string mysql_subscriber_service_subscriber_id = "UPDATE subscriber_connected_services "
				"SET subscriber_id = '"+subscriber_id+"', service_status = 'processed' "
				"WHERE subscriber_connected_services.service_status = 'not_processed'";
		query_state=mysql_query(conn, mysql_subscriber_service_subscriber_id.c_str());

		if(query_state!=0)
		{
			  std::cout<<mysql_error(conn)<<std::endl<<std::endl;
		}



		// subscriber contacts data write in mysql table
		contact_numbers = ui->contact_number_edit->text().toUTF8();

		std::string mysql_subscriber_contacts = "INSERT INTO contacts (subscriber_id, city, district, "
				"street, housing, floor, house, apartment, index_number, contact_numbers) "
				"values ('"+subscriber_id+"', '"+city+"', '"+district+"','"+street+"', '"+housing+"','"+house_floor+"', "
						"'"+house+"','"+apartment+"', '"+index_number+"','"+contact_numbers+"')";
		query_state=mysql_query(conn, mysql_subscriber_contacts.c_str());
		if(query_state!=0)
				{
					  std::cout<<mysql_error(conn)<<std::endl<<std::endl;
				}






//get subscriber requisites and information fields data and write in mysql tables

		// get subscriber requisites data
		personal_code = ui->personal_code_edit->text().toUTF8();
		organization_code = ui->organization_code_edit->text().toUTF8();
		tax_code =  ui->tax_code_edit->text().toUTF8();
		account =  ui->requisite_account_edit->text().toUTF8();
		bank_code =  ui->bank_code_edit->text().toUTF8();
		agreement =  ui->agreement_edit->text().toUTF8();

		if (ui->agreement_checkbox->isChecked())
		{
			ui->agreement_date_edit->setFormat("yyyy-MM-dd");
			agreement_date = ui->agreement_date_edit->text().narrow(); // may occur error narrow()
		}

		// write requisites in mysql table
		std::string mysql_subscriber_requisites = "INSERT INTO requisites (subscriber_id, personal_code, "
				"organization_code, tax_code, account, bank_code, agreement, agreement_date) "
				"values ('"+subscriber_id+"', '"+personal_code+"', '"+organization_code+"', '"+tax_code+"', "
						"'"+account+"', '"+bank_code+"', '"+agreement+"', '"+agreement_date+"')";
		query_state=mysql_query(conn, mysql_subscriber_requisites.c_str());
		if(query_state!=0)
				{
					  std::cout<<mysql_error(conn)<<std::endl<<std::endl;
				}


		// get subscriber information fields data
		description = ui->description_text_area->text().toUTF8();
		information = ui->information_text_area->text().toUTF8();
		//subscriber_id = "1";
		// write information fields in mysql table
		std::string mysql_subscriber_information_fields = "INSERT INTO information_fields (subscriber_id, description, "
				"information) values ('"+subscriber_id+"', '"+description+"', '"+information+"')";
		query_state=mysql_query(conn, mysql_subscriber_information_fields.c_str());
		if(query_state!=0)
				{
					  std::cout<<mysql_error(conn)<<std::endl<<std::endl;
				}

		std::cout << "Creat user init END" << "***************************************************" << std::endl;
	// clear all data variables

		// subscriber group info variable
		std::string group_name = "";

		// subscriber contacts data variables
		subscriber_id = "";
		group_id = "";
		name = "";
		surname = "";
		patronymic = "";
		full_name = "";
		subscriber_type = "";
		account_number = "";
		user_login = "";
		user_password = "";
		date_since = "";
		date_by = "";
		tariff_plan  = "";
		user_email = "";

		// subscriber contacts data variables
		city = "";
		district = "";
		street = "";
		housing = "";
		house_floor = "";
		house = "";
		apartment = "";
		index_number = "";
		contact_numbers = "";

		// subscriber requisites data variables
		personal_code = "";
		organization_code = "";
		tax_code = "";
		account = "";
		bank_code = "";
		agreement = "";
		agreement_date = "";

		// subscriber information fields data variables
		description = "";
		information = "";

		// close(hide) this tab
		ui->create_user_tab_mi->setHidden(true);
		ui->main_tabs->setCurrentIndex(0);

		//mysql_free_result(res);
		mysql_close(conn);

		} catch (const std::exception& e) {std::cout <<"Creat user main -> "<< e.what()<<std::endl;}
	} else // operation_name == "create" ############################################################################
	{
		try {
		mysql_init(&mysql);
		conn=mysql_real_connect(&mysql, server, user, password, database, 0, 0, 0);
		if(conn==NULL)
		{
			std::cout<<mysql_error(&mysql)<<std::endl<<std::endl;
		}
		mysql_query(&mysql,"SET NAMES 'UTF8'");
		if(conn==NULL)
		{
			std::cout<<mysql_error(&mysql)<<std::endl<<std::endl;
		}


// get group id through group name
		if(!new_group_name_edit_mode.empty())
		{
			std::string old_group_id_edit_mode = group_id_edit_mode; // saved in variable group id from mysql table
			mysql_query_str = "select group_id from subscriber_group where group_name = '"+new_group_name_edit_mode+"'";
			query_state=mysql_query(conn, mysql_query_str.c_str());
			if(query_state!=0)
			{
			   std::cout<<mysql_error(conn)<<std::endl<<std::endl;
			}
			res=mysql_store_result(conn);
			std::cout<<"MySQL Values in the amaDB Table.11"<<std::endl<<std::endl;
			row=mysql_fetch_row(res);
			group_id_edit_mode = boost::lexical_cast<std::string>(row[0]); // get group id for new group name
			mysql_free_result(res);
			// if subscriber group changed decrease subscribers_number_ingroup in old group and increase in new group
			if (new_group_name_edit_mode != group_name_edit_mode) {
				mysql_query_str = "UPDATE subscriber_group SET subscribers_number_ingroup = subscribers_number_ingroup - 1 WHERE group_id = '"+old_group_id_edit_mode+"'";
				query_state=mysql_query(conn, mysql_query_str.c_str());
				if(query_state!=0)
				{
					std::cout<<mysql_error(conn)<<std::endl<<std::endl;
				}

				mysql_query_str = "UPDATE subscriber_group SET subscribers_number_ingroup = subscribers_number_ingroup + 1 WHERE group_id = '"+group_id_edit_mode+"'";
				query_state=mysql_query(conn, mysql_query_str.c_str());
				if(query_state!=0)
				{
					std::cout<<mysql_error(conn)<<std::endl<<std::endl;
				}
			}
		}



// get info from some form entry where not updates value automatically(i.e when dialog window close value in some variable change this variable I'm not change)
			// get main subscriber info
			full_name_edit_mode = ui->user_full_name_edit_edit_user_tab->text().toUTF8();
			subscriber_type_edit_mode = ui->user_type_combo_box_edit_user_tab->currentText().toUTF8();
			account_number_edit_mode = ui->account_number_edit_edit_user_tab->text().narrow();
			user_login_edit_mode = ui->user_login_edit_edit_user_tab->text().toUTF8();
			user_password_edit_mode = ui->user_pass_edit_edit_user_tab->text().toUTF8();
			tariff_plan_edit_mode = ui->tariff_plan_edit_edit_user_tab->text().toUTF8();
			user_email_edit_mode = ui->user_email_edit_edit_user_tab->text().narrow();

			if (ui->user_include_date_checkbox_edit_user_tab->isChecked())
			{
				ui->user_include_date_date_edit_edit_user_tab->setFormat("yyyy-MM-dd");
				date_since_edit_mode = boost::lexical_cast<std::string>(ui->user_include_date_date_edit_edit_user_tab->text());
			}
			else
			{
				date_since_edit_mode = "";
			}


			if (ui->user_disable_date_checkbox_edit_user_tab->isChecked())
			{
				ui->user_disable_date_date_edit_edit_user_tab->setFormat("yyyy-MM-dd");
				date_by_edit_mode = boost::lexical_cast<std::string>(ui->user_disable_date_date_edit_edit_user_tab->text());
			}
			else
			{
				date_by_edit_mode = "";
			}

			// get subscriber contact numbers
			contact_numbers_edit_mode = ui->contact_number_edit_edit_user_tab->text().narrow();

			// get subscriber requisites data
			personal_code_edit_mode = ui->personal_code_edit_edit_user_tab->text().toUTF8();
			organization_code_edit_mode = ui->organization_code_edit_edit_user_tab->text().toUTF8();
			tax_code_edit_mode =  ui->tax_code_edit_edit_user_tab->text().toUTF8();
			account_edit_mode =  ui->requisite_account_edit_edit_user_tab->text().toUTF8();
			bank_code_edit_mode =  ui->bank_code_edit_edit_user_tab->text().toUTF8();
			agreement_edit_mode =  ui->agreement_edit_edit_user_tab->text().toUTF8();

			if (ui->agreement_checkbox_edit_user_tab->isChecked())
			{
				ui->agreement_date_edit_edit_user_tab->setFormat("yyyy-MM-dd");
				agreement_date_edit_mode = ui->agreement_date_edit_edit_user_tab->text().narrow(); // may occur error narrow()
			}
			else
			{
				agreement_date_edit_mode = "";
			}


			// get subscriber information fields data
			description_edit_mode = ui->description_text_area_edit_user_tab->text().toUTF8();
			information_edit_mode = ui->information_text_area_edit_user_tab->text().toUTF8();



		// update all subscriber information
		std::string mysql_subscriber_update_all_data = "UPDATE subscriber_group, subscriber, contacts, requisites, information_fields "
						"SET subscriber.group_id = '"+group_id_edit_mode+"', name = '"+name_edit_mode+"', surname = '"+surname_edit_mode+"', "
						"patronymic = '"+patronymic_edit_mode+"', full_name = '"+full_name_edit_mode+"', subscriber_type = '"+subscriber_type_edit_mode+"', "
						"account_number = '"+account_number_edit_mode+"', user_login = '"+user_login_edit_mode+"', user_password = '"+user_password_edit_mode+"', "
						"date_since = '"+date_since_edit_mode+"', date_by = '"+date_by_edit_mode+"', tariff_plan = '"+tariff_plan_edit_mode+"', "
						"user_email = '"+user_email_edit_mode+"', city = '"+city_edit_mode+"', district = '"+district_edit_mode+"', street = '"+street_edit_mode+"', "
						"housing = '"+housing_edit_mode+"', floor = '"+house_floor_edit_mode+"', house = '"+house_edit_mode+"', apartment = '"+apartment_edit_mode+"', "
						"index_number = '"+index_number_edit_mode+"', contact_numbers = '"+contact_numbers_edit_mode+"', personal_code = '"+personal_code_edit_mode+"', "
						"organization_code = '"+organization_code_edit_mode+"', tax_code = '"+tax_code_edit_mode+"', account = '"+account_edit_mode+"', "
						"bank_code = '"+bank_code_edit_mode+"', agreement = '"+agreement_edit_mode+"', agreement_date = '"+agreement_date_edit_mode+"', "
						"description = '"+description_edit_mode+"', information = '"+information_edit_mode+"' "
						"WHERE subscriber.subscriber_id = '"+subscriber_id_edit_mode+"' AND subscriber_group.group_id = subscriber.group_id "
						"AND subscriber.subscriber_id = contacts.subscriber_id AND contacts.subscriber_id = requisites.subscriber_id "
						"AND requisites.subscriber_id = information_fields.subscriber_id";

		query_state=mysql_query(conn, mysql_subscriber_update_all_data.c_str());
		if(query_state!=0)
				{
					  std::cout<<mysql_error(conn)<<std::endl<<std::endl;
				}


// clear all data variables

		// subscriber group info variable
		group_name_edit_mode = "";

		// subscriber contacts data variables
		subscriber_id_edit_mode = "";
		group_id_edit_mode = "";
		name_edit_mode = "";
		surname_edit_mode = "";
		patronymic_edit_mode = "";
		full_name_edit_mode = "";
		subscriber_type_edit_mode = "";
		account_number_edit_mode = "";
		user_login_edit_mode = "";
		user_password_edit_mode = "";
		date_since_edit_mode = "";
		date_by_edit_mode = "";
		tariff_plan_edit_mode  = "";
		user_email_edit_mode = "";

		// subscriber contacts data variables
		city_edit_mode = "";
		district_edit_mode = "";
		street_edit_mode = "";
		housing_edit_mode = "";
		house_floor_edit_mode = "";
		house_edit_mode = "";
		apartment_edit_mode = "";
		index_number_edit_mode = "";
		contact_numbers_edit_mode = "";

		// subscriber requisites data variables
		personal_code_edit_mode = "";
		organization_code_edit_mode = "";
		tax_code_edit_mode = "";
		account_edit_mode = "";
		bank_code_edit_mode = "";
		agreement_edit_mode = "";
		agreement_date_edit_mode = "";

		// subscriber information fields data variables
		description_edit_mode = "";
		information_edit_mode = "";

		// close(hide) this tab
		ui->edit_user_tab_mi->setHidden(true);
		ui->main_tabs->setCurrentIndex(0);

		//mysql_free_result(res);
		mysql_close(conn);
		} catch (const std::exception& e) {std::cout <<"Edit user main -> "<< e.what()<<std::endl;}
	}

}



// services %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%








// show dialog window where you can create new services
extern void WtAccounts::create_new_service_dialog()
{
    Wt::WDialog *dialog = new Wt::WDialog(Wt::WString::fromUTF8("Услуги"));

    dialog->resize(600, 750);



	// dialog contents
    // service name label and edit
    Wt::WLabel *service_name_label = new Wt::WLabel(Wt::WString::fromUTF8("Название:"),
    				       dialog->contents());
    service_name_label->setStyleClass("col-lg-3 col-md-3 top_pad top_mar");

    Wt::WContainerWidget *service_name_edit_container = new Wt::WContainerWidget(dialog->contents());
    service_name_edit_container->setStyleClass(Wt::WString::fromUTF8("col-md-9 col-lg-9 top_mar"));
    service_name_edit_container->setHtmlTagName("div");

    Wt::WLineEdit *service_name_edit = new Wt::WLineEdit(service_name_edit_container);
    service_name_edit->setText(Wt::WString::fromUTF8(""));
    service_name_label->setBuddy(service_name_edit);



    // code label and edit
    Wt::WLabel *code_label = new Wt::WLabel(Wt::WString::fromUTF8("Код:"),
    				       dialog->contents());
    code_label->setStyleClass("col-lg-3 col-md-3 top_pad top_mar");

    Wt::WContainerWidget *code_edit_container = new Wt::WContainerWidget(dialog->contents());
    code_edit_container->setStyleClass(Wt::WString::fromUTF8("col-md-9 col-lg-9 top_mar"));
    code_edit_container->setHtmlTagName("div");

    Wt::WLineEdit *code_edit = new Wt::WLineEdit(code_edit_container);
    code_edit->setText(Wt::WString::fromUTF8(""));
    code_label->setBuddy(code_edit);



    // charging period label and combo box
    Wt::WLabel *charging_period_label = new Wt::WLabel(Wt::WString::fromUTF8("Период начисления:"),
    				       dialog->contents());
    charging_period_label->setStyleClass("col-lg-3 col-md-3 top_pad top_mar");

    Wt::WContainerWidget *charging_period_combobox_container = new Wt::WContainerWidget(dialog->contents());
    charging_period_combobox_container->setStyleClass(Wt::WString::fromUTF8("col-md-9 col-lg-9 top_mar"));
    charging_period_combobox_container->setHtmlTagName("div");

    Wt::WComboBox *charging_period_combobox = new Wt::WComboBox(charging_period_combobox_container);
    charging_period_label->setBuddy(charging_period_combobox);


	charging_period_combobox->addItem(Wt::WString::fromUTF8("Ручное начисление"));
	charging_period_combobox->addItem(Wt::WString::fromUTF8("Каждый день"));
	charging_period_combobox->addItem(Wt::WString::fromUTF8("Каждую неделю"));
	charging_period_combobox->addItem(Wt::WString::fromUTF8("Каждый месяц"));
	charging_period_combobox->addItem(Wt::WString::fromUTF8("Каждый год"));
	charging_period_combobox->addItem(Wt::WString::fromUTF8("Особый сценарий"));
	charging_period_combobox->addItem(Wt::WString::fromUTF8("Авто"));



    // description label and text area
    Wt::WLabel *description_label = new Wt::WLabel(Wt::WString::fromUTF8("Описание:"),
    				       dialog->contents());
    description_label->setStyleClass("col-lg-3 col-md-3 top_pad top_mar");

    Wt::WContainerWidget *description_text_area_container = new Wt::WContainerWidget(dialog->contents());
    description_text_area_container->setStyleClass(Wt::WString::fromUTF8("col-md-9 col-lg-9 top_mar"));
    description_text_area_container->setHtmlTagName("div");

    Wt::WTextArea *description_text_area = new Wt::WTextArea(description_text_area_container);
    description_text_area->setColumns(80);
    description_text_area->setRows(3);
    description_label->setBuddy(description_text_area);



    // service tariff label and edit
    Wt::WLabel *service_tariff_label = new Wt::WLabel(Wt::WString::fromUTF8("Тариф:"),
    				       dialog->contents());
    service_tariff_label->setStyleClass("col-lg-3 col-md-3 top_pad top_mar");

    Wt::WContainerWidget *service_tariff_edit_container = new Wt::WContainerWidget(dialog->contents());
    service_tariff_edit_container->setStyleClass(Wt::WString::fromUTF8("col-md-9 col-lg-9 top_mar"));
    service_tariff_edit_container->setHtmlTagName("div");

    Wt::WLineEdit *service_tariff_edit = new Wt::WLineEdit(service_tariff_edit_container);
    service_tariff_edit->setText(Wt::WString::fromUTF8("Фиксированная  сумма"));
    service_tariff_label->setBuddy(service_tariff_edit);



    // fixed sum label and edit
    Wt::WLabel *fixed_sum_label = new Wt::WLabel(Wt::WString::fromUTF8("Фикс. сумма:"),
    				       dialog->contents());
    fixed_sum_label->setStyleClass("col-lg-3 col-md-3 top_pad top_mar");

    Wt::WContainerWidget *fixed_sum_edit_container = new Wt::WContainerWidget(dialog->contents());
    fixed_sum_edit_container->setStyleClass(Wt::WString::fromUTF8("col-md-9 col-lg-9 top_mar"));
    fixed_sum_edit_container->setHtmlTagName("div");

    Wt::WLineEdit *fixed_sum_edit = new Wt::WLineEdit(fixed_sum_edit_container);
    fixed_sum_edit->setText(Wt::WString::fromUTF8(""));
    fixed_sum_label->setBuddy(fixed_sum_edit);



    // currency label and edit
    Wt::WLabel *currency_label = new Wt::WLabel(Wt::WString::fromUTF8("Валюта:"),
    				       dialog->contents());
    currency_label->setStyleClass("col-lg-3 col-md-3 top_pad top_mar");

    Wt::WContainerWidget *currency_edit_container = new Wt::WContainerWidget(dialog->contents());
    currency_edit_container->setStyleClass(Wt::WString::fromUTF8("col-md-9 col-lg-9 top_mar"));
    currency_edit_container->setHtmlTagName("div");

    Wt::WLineEdit *currency_edit = new Wt::WLineEdit(currency_edit_container);
    currency_edit->setText(Wt::WString::fromUTF8("KZT (Тенге)"));
    currency_label->setBuddy(currency_edit);



/*
    // include date label, check box and date edit
    Wt::WLabel *include_date_label = new Wt::WLabel(Wt::WString::fromUTF8("С:"),
    				       dialog->contents());
    include_date_label->setStyleClass("col-lg-3 col-md-3 top_pad top_mar");


    Wt::WCheckBox *include_date_checkbox = new Wt::WCheckBox("", dialog->contents());
    include_date_checkbox->setStyleClass("col-lg-1 col-md-1 top_pad");

    Wt::WContainerWidget *include_date_edit_container = new Wt::WContainerWidget(dialog->contents());
    include_date_edit_container->setStyleClass(Wt::WString::fromUTF8("col-md-8 col-lg-8 top_mar"));
    include_date_edit_container->setHtmlTagName("div");

    Wt::WDateEdit *include_date_edit = new Wt::WDateEdit(include_date_edit_container);
    include_date_edit->setFormat("yyyy-MM-dd");
    include_date_label->setBuddy(include_date_edit);



    // disable date label, check box and date edit
    Wt::WLabel *disable_date_label = new Wt::WLabel(Wt::WString::fromUTF8("По:"),
    				       dialog->contents());
    disable_date_label->setStyleClass("col-lg-3 col-md-3 top_pad top_mar");


    Wt::WCheckBox *disable_date_checkbox = new Wt::WCheckBox("", dialog->contents());
    disable_date_checkbox->setStyleClass("col-lg-1 col-md-1 top_pad");

    Wt::WContainerWidget *disable_date_edit_container = new Wt::WContainerWidget(dialog->contents());
    disable_date_edit_container->setStyleClass(Wt::WString::fromUTF8("col-md-8 col-lg-8 top_mar"));
    disable_date_edit_container->setHtmlTagName("div");

    Wt::WDateEdit *disable_date_edit = new Wt::WDateEdit(disable_date_edit_container);
    disable_date_edit->setFormat("yyyy-MM-dd");
    disable_date_label->setBuddy(disable_date_edit);
*/



    dialog->contents()->addStyleClass("form-group");


    Wt::WPushButton *ok = new Wt::WPushButton("OK", dialog->footer());
    ok->setDefault(true);


    Wt::WPushButton *cancel = new Wt::WPushButton("Cancel", dialog->footer());
    dialog->rejectWhenEscapePressed();



    // Accept the dialog
    ok->clicked().connect(std::bind([=] () {
	    dialog->accept();
    }));


    // Reject the dialog
    cancel->clicked().connect(dialog, &Wt::WDialog::reject);


    // Process the dialog result.
    dialog->finished().connect(std::bind([=] () {
	if (dialog->result() == Wt::WDialog::Accepted)
	{

		std::string service_name = "";
		std::string code = "";
		std::string charging_period = "";
		std::string description = "";
		std::string service_tariff = "";
		std::string fixed_sum = "";
		std::string currency = "";

		mysql_init(&mysql);
		conn=mysql_real_connect(&mysql, server, user, password, database, 0, 0, 0);
		if(conn==NULL)
		{
		    std::cout<<mysql_error(&mysql)<<std::endl<<std::endl;
		}
		mysql_query(&mysql,"SET NAMES 'UTF8'");



		service_name = service_name_edit->text().toUTF8();;
		code = code_edit->text().toUTF8();;
		charging_period = charging_period_combobox->currentText().toUTF8();
		description = description_text_area->text().toUTF8();;
		service_tariff = service_tariff_edit->text().toUTF8();;
		fixed_sum = fixed_sum_edit->text().toUTF8();;
		currency = currency_edit->text().toUTF8();;

		std::string mysql_insert_create_service = "INSERT INTO subscriber_services "
					"(service_name, code, charging_period, description, service_tariff, "
					"amount, currency) "
					"values ('"+ service_name +"', '"+ code +"', '"+ charging_period +"', "
					"'"+ description +"', '"+ service_tariff +"', '"+ fixed_sum +"',  "
					"'"+ currency +"')";


		query_state=mysql_query(conn, mysql_insert_create_service.c_str());
		if(query_state!=0)
		{
			std::cout<<mysql_error(conn)<<std::endl<<std::endl;
		}


		service_table->clear();
		service_table->elementAt(0, 0)->addWidget(new Wt::WText(Wt::WString::fromUTF8("Название")));
		service_table->elementAt(0, 1)->addWidget(new Wt::WText(Wt::WString::fromUTF8("Период начисления")));
		service_table->elementAt(0, 2)->addWidget(new Wt::WText(Wt::WString::fromUTF8("Код")));
		service_table->elementAt(0, 3)->addWidget(new Wt::WText(Wt::WString::fromUTF8("Тариф")));
		service_table->elementAt(0, 4)->addWidget(new Wt::WText(Wt::WString::fromUTF8("Фикс. сумма")));
		service_table->elementAt(0, 5)->addWidget(new Wt::WText(Wt::WString::fromUTF8("Валюта")));

		int row_number = 0;



		std::string mysql_service_table_data = "SELECT service_name, code, charging_period, "
					"service_tariff, amount, currency FROM subscriber_services";

		query_state=mysql_query(conn, mysql_service_table_data.c_str());
		if(query_state!=0)
		{
		   std::cout<<mysql_error(conn)<<std::endl<<std::endl;
		}
		res=mysql_store_result(conn);
		while((row=mysql_fetch_row(res))!=NULL)
		{
			row_number++;
			new Wt::WText(Wt::WString::fromUTF8(row[0]), service_table->elementAt(row_number, 0));
			new Wt::WText(Wt::WString::fromUTF8(row[2]), service_table->elementAt(row_number, 1));
			new Wt::WText(Wt::WString::fromUTF8(row[1]), service_table->elementAt(row_number, 2));
			new Wt::WText(Wt::WString::fromUTF8(row[3]), service_table->elementAt(row_number, 3));
			new Wt::WText(Wt::WString::fromUTF8(row[4]), service_table->elementAt(row_number, 4));
			new Wt::WText(Wt::WString::fromUTF8(row[5]), service_table->elementAt(row_number, 5));
		}
		service_table->refresh();
		mysql_free_result(res);
		mysql_close(conn);
	}

	delete dialog;
    }));

    dialog->show();
}









// show dialog window where you manage services (create)
extern void WtAccounts::manage_services_dialog()
{
    Wt::WDialog *dialog = new Wt::WDialog(Wt::WString::fromUTF8("Услуги"));

    dialog->resize(1050, 650);



    // srevice top buttons
    Wt::WPushButton *save_exit_button = new Wt::WPushButton(Wt::WString::fromUTF8("Сохранить и закрыть"), dialog->contents());
    save_exit_button->setStyleClass(Wt::WString::fromUTF8("btn btn-default with-label col-md-3 col-lg-3"));

    Wt::WPushButton *add_service_button = new Wt::WPushButton(Wt::WString::fromUTF8("Добавить"), dialog->contents());
    add_service_button->setStyleClass(Wt::WString::fromUTF8("btn btn-default with-label col-md-3 col-lg-3"));

    //Wt::WPushButton *change_ip_button = new Wt::WPushButton(Wt::WString::fromUTF8("Изменить"), dialog->contents());
    //change_ip_button->setStyleClass(Wt::WString::fromUTF8("btn btn-default with-label col-md-1 col-lg-1"));

    //Wt::WPushButton *delete_service_button = new Wt::WPushButton(Wt::WString::fromUTF8("Удалить"), dialog->contents());
    //delete_service_button->setStyleClass(Wt::WString::fromUTF8("btn btn-default with-label col-md-3 col-lg-3"));


	add_service_button->clicked().connect(boost::bind(&WtAccounts::create_new_service_dialog, this));
	//delete_service_button->clicked().connect(boost::bind(&WtAccounts::delete_service_dialog, this, operation_name));



	mysql_init(&mysql);
	conn=mysql_real_connect(&mysql, server, user, password, database, 0, 0, 0);
	if(conn==NULL)
	{
	    std::cout<<mysql_error(&mysql)<<std::endl<<std::endl;
	}
	mysql_query(&mysql,"SET NAMES 'UTF8'");


	// container for table with data about ip address
    Wt::WContainerWidget *service_table_container = new Wt::WContainerWidget(dialog->contents());
    //service_table_container->setStyleClass(Wt::WString::fromUTF8("col-md-9 col-lg-9 top_mar"));
    service_table_container->setHtmlTagName("div");
    service_table_container->setWidth(Wt::WLength("100%"));
    service_table_container->setHeight(Wt::WLength("450px"));
    service_table_container->setOverflow(Wt::WContainerWidget::Overflow::OverflowAuto, Wt::Orientation::Vertical);

	// table with data about ip address
	service_table = new Wt::WTable(service_table_container);
	service_table->setHeaderCount(1);
	service_table->setWidth(Wt::WLength("100%"));
	//service_table->setHeight(Wt::WLength("50%"));
	//service_table->setHeight(Wt::WLength("100px"));
	//service_table->resize(1000, 100);
	//service_table


	service_table->setHeaderCount(1);

	//service_table->resize();
	service_table->elementAt(0, 0)->addWidget(new Wt::WText(Wt::WString::fromUTF8("Название")));
	service_table->elementAt(0, 1)->addWidget(new Wt::WText(Wt::WString::fromUTF8("Период начисления")));
	service_table->elementAt(0, 2)->addWidget(new Wt::WText(Wt::WString::fromUTF8("Код")));
	service_table->elementAt(0, 3)->addWidget(new Wt::WText(Wt::WString::fromUTF8("Тариф")));
	service_table->elementAt(0, 4)->addWidget(new Wt::WText(Wt::WString::fromUTF8("Фикс. сумма")));
	service_table->elementAt(0, 5)->addWidget(new Wt::WText(Wt::WString::fromUTF8("Валюта")));

	int row_number = 0;



	std::string mysql_service_table_data = "SELECT service_name, code, charging_period, "
				"service_tariff, amount, currency FROM subscriber_services";

	query_state=mysql_query(conn, mysql_service_table_data.c_str());
	if(query_state!=0)
	{
	   std::cout<<mysql_error(conn)<<std::endl<<std::endl;
	}
	res=mysql_store_result(conn);
	while((row=mysql_fetch_row(res))!=NULL)
	{
		row_number++;
		new Wt::WText(Wt::WString::fromUTF8(row[0]), service_table->elementAt(row_number, 0));
		new Wt::WText(Wt::WString::fromUTF8(row[2]), service_table->elementAt(row_number, 1));
		new Wt::WText(Wt::WString::fromUTF8(row[1]), service_table->elementAt(row_number, 2));
		new Wt::WText(Wt::WString::fromUTF8(row[3]), service_table->elementAt(row_number, 3));
		new Wt::WText(Wt::WString::fromUTF8(row[4]), service_table->elementAt(row_number, 4));
		new Wt::WText(Wt::WString::fromUTF8(row[5]), service_table->elementAt(row_number, 5));
	}
	row_number = 0;
	service_table->addStyleClass("table form-inline table-bordered table-hover table-condensed table-striped top_mar top_pad");


	mysql_free_result(res);
	mysql_close(conn);;



    dialog->contents()->addStyleClass("form-group");



    //Wt::WPushButton *ok = new Wt::WPushButton("OK", dialog->footer());
    //ok->setDefault(true);


    Wt::WPushButton *cancel = new Wt::WPushButton("Cancel", dialog->footer());
    dialog->rejectWhenEscapePressed();



    // Accept the dialog
    save_exit_button->clicked().connect(std::bind([=] () {
	    dialog->accept();
    }));


    // Reject the dialog
    cancel->clicked().connect(dialog, &Wt::WDialog::reject);


    // Process the dialog result.
    dialog->finished().connect(std::bind([=] () {
	if (dialog->result() == Wt::WDialog::Accepted)
	{
	}

	delete dialog;
    }));

    dialog->show();
}





// bind functions to account operation popup items
extern void WtAccounts::account_operation_popup_item_binder()
{

	std::string popup_menu_selected_item = ui->p_account_operation_split_button_popup->result()->text().toUTF8();

	if (popup_menu_selected_item == "Начислить услуги вручную")
	{
		WtAccounts::subscriber_add_one_time_services_dialog();
	} else if (popup_menu_selected_item == "Ввести оплату")
	{
		WtAccounts::subscriber_payment_transaction_dialog();
	}
	else if (popup_menu_selected_item == "Завести первоначальный долг")
	{
		WtAccounts::subscriber_initial_debt_dialog();
	}
	else if (popup_menu_selected_item == "Разослать квитанции")
		{
			WtAccounts::send_mail_to_users();
		}
	else
	{
		WtAccounts::p_account_operation_CHECK("herdre");
	}

}





//
extern void WtAccounts::subscriber_add_one_time_services_dialog()
{
    Wt::WDialog *dialog = new Wt::WDialog(Wt::WString::fromUTF8("Начисление услуги"));

    dialog->resize(800, 750);

	mysql_init(&mysql);
	conn=mysql_real_connect(&mysql, server, user, password, database, 0, 0, 0);
	if(conn==NULL)
	{
	    std::cout<<mysql_error(&mysql)<<std::endl<<std::endl;
	}
	mysql_query(&mysql,"SET NAMES 'UTF8'");



// dialog contents
    Wt::WTreeTable *treeTable;
	treeTable = new Wt::WTreeTable(dialog->contents());
    treeTable->resize(750, 400);
    //treeTable->setStyleClass(Wt::WString::fromUTF8("Wt-treetable col-lg-12 col-md-12"));
    treeTable->setStyleClass(Wt::WString::fromUTF8("Wt-treetable"));
    treeTable->tree()->setSelectionMode(Wt::SingleSelection);
    treeTable->addColumn(Wt::WString::fromUTF8("Стоимость"), 100);


    Wt::WTreeTableNode *tree_root;
	tree_root = new Wt::WTreeTableNode(Wt::WString::fromUTF8("Услуга"));
    treeTable->setTreeRoot(tree_root, Wt::WString::fromUTF8("Названия"));

    Wt::WTreeTableNode *tree_node;



// add node form mysql table
	query_state=mysql_query(conn, "SELECT * FROM subscriber_services WHERE charging_period = 'Ручное начисление'");
	if(query_state!=0)
	{
	   std::cout<<mysql_error(conn)<<std::endl<<std::endl;
	}
	res=mysql_store_result(conn);
	std::cout<<"MySQL Values in the amaDB Table.12"<<std::endl<<std::endl;
	while((row=mysql_fetch_row(res))!=NULL)
	{
		tree_node  = new Wt::WTreeTableNode(Wt::WString::fromUTF8(row[1]), 0, tree_root);
		tree_node ->setColumnWidget(1, new Wt::WText(Wt::WString::fromUTF8(row[7])));
	}


	mysql_free_result(res);

	tree_root->expand();





    // number/ip label and combo box
    Wt::WLabel *number_ip_label = new Wt::WLabel(Wt::WString::fromUTF8("Номер/IP:"),
    				       dialog->contents());
    number_ip_label->setStyleClass("col-lg-2 col-md-2 top_pad top_mar");

    Wt::WContainerWidget *number_ip_combobox_container = new Wt::WContainerWidget(dialog->contents());
    number_ip_combobox_container->setStyleClass(Wt::WString::fromUTF8("col-md-10 col-lg-10 top_mar"));
    number_ip_combobox_container->setHtmlTagName("div");

    Wt::WComboBox *number_ip_combobox = new Wt::WComboBox(number_ip_combobox_container);
    number_ip_label->setBuddy(number_ip_combobox);

    std::string mysql_get_number_ip = "SELECT ip_address FROM ip_addresses "
    			"WHERE ip_addresses.subscriber_id = '"+ subscriber_id_edit_mode +"'";
	query_state=mysql_query(conn, mysql_get_number_ip.c_str());
	if(query_state!=0)
	{
		std::cout<<mysql_error(conn)<<std::endl<<std::endl;
	}
	res=mysql_store_result(conn);

	number_ip_combobox->addItem(Wt::WString::fromUTF8(" ")); // if we not set IP or phone number

	while((row=mysql_fetch_row(res))!=NULL)
	{
		number_ip_combobox->addItem(Wt::WString::fromUTF8(row[0]));
	}

    mysql_get_number_ip = "SELECT number FROM phone_numbers "
    			"WHERE phone_numbers.subscriber_id = '"+ subscriber_id_edit_mode +"'";
	query_state=mysql_query(conn, mysql_get_number_ip.c_str());
	if(query_state!=0)
	{
		std::cout<<mysql_error(conn)<<std::endl<<std::endl;
	}
	res=mysql_store_result(conn);
	while((row=mysql_fetch_row(res))!=NULL)
	{
			number_ip_combobox->addItem(Wt::WString::fromUTF8(row[0]));
	}




    // total label and edit
    Wt::WLabel *total_label = new Wt::WLabel(Wt::WString::fromUTF8("Сумма:"),
    				       dialog->contents());
    total_label->setStyleClass("col-lg-2 col-md-2 top_pad top_mar");

    Wt::WContainerWidget *total_edit_container = new Wt::WContainerWidget(dialog->contents());
    total_edit_container->setStyleClass(Wt::WString::fromUTF8("col-md-3 col-lg-3 top_mar"));
    total_edit_container->setHtmlTagName("div");

    Wt::WLineEdit *total_edit = new Wt::WLineEdit(total_edit_container);
    total_edit->setText(Wt::WString::fromUTF8(""));
    total_label->setBuddy(total_edit);





    // credit date label and date edit
    Wt::WLabel *credit_date_label = new Wt::WLabel(Wt::WString::fromUTF8("Дата начисления:"),
    				       dialog->contents());
    credit_date_label->setStyleClass("col-lg-2 col-md-2 top_pad top_mar");

    Wt::WContainerWidget *credit_date_edit_container = new Wt::WContainerWidget(dialog->contents());
    credit_date_edit_container->setStyleClass(Wt::WString::fromUTF8("col-md-5 col-lg-5 top_mar"));
    credit_date_edit_container->setHtmlTagName("div");

    Wt::WDateEdit *credit_date_edit = new Wt::WDateEdit(credit_date_edit_container);
    credit_date_edit->setFormat("yyyy-MM-dd");
    credit_date_label->setBuddy(credit_date_edit);





    // description label and text area
    Wt::WLabel *description_label = new Wt::WLabel(Wt::WString::fromUTF8("Описание:"),
    				       dialog->contents());
    description_label->setStyleClass("col-lg-2 col-md-2 top_pad top_mar");

    Wt::WContainerWidget *description_text_area_container = new Wt::WContainerWidget(dialog->contents());
    description_text_area_container->setStyleClass(Wt::WString::fromUTF8("col-md-10 col-lg-10 top_mar"));
    description_text_area_container->setHtmlTagName("div");

    Wt::WTextArea *description_text_area = new Wt::WTextArea(description_text_area_container);
    description_text_area->setColumns(80);
    description_text_area->setRows(3);
    description_label->setBuddy(description_text_area);

	mysql_free_result(res);
	mysql_close(conn);



    dialog->contents()->addStyleClass("form-group");


    Wt::WPushButton *ok = new Wt::WPushButton("OK", dialog->footer());
    ok->setDefault(true);


    Wt::WPushButton *cancel = new Wt::WPushButton("Cancel", dialog->footer());
    dialog->rejectWhenEscapePressed();



    // Accept the dialog
    ok->clicked().connect(std::bind([=] () {
	    dialog->accept();
    }));


    // Reject the dialog
    cancel->clicked().connect(dialog, &Wt::WDialog::reject);


    // Process the dialog result.
    dialog->finished().connect(std::bind([=] () {
	if (dialog->result() == Wt::WDialog::Accepted)
	{

		std::string service_name = "";
		std::string number_ip = "";
		std::string total_cost = "";
		std::string credit_date = "";
		std::string description = "";



		Wt::WTreeNode *selected_node; // operator* returns contents of an interator
		std::set<Wt::WTreeNode* > highlightedRows = treeTable->tree()->selectedNodes();
		if (!highlightedRows.empty())
		{
			for (std::set<Wt::WTreeNode* >::iterator i = highlightedRows.begin(); i != highlightedRows.end(); ++i)
			{
			  selected_node = *i;
			}
			service_name = selected_node->label()->text().toUTF8();
			highlightedRows.clear();
		}



		mysql_init(&mysql);
		conn=mysql_real_connect(&mysql, server, user, password, database, 0, 0, 0);
		if(conn==NULL)
		{
		    std::cout<<mysql_error(&mysql)<<std::endl<<std::endl;
		}
		mysql_query(&mysql,"SET NAMES 'UTF8'");



		std::string mysql_get_total_cost = "SELECT amount FROM subscriber_services "
	    			"WHERE service_name = '"+ service_name  +"'";
		query_state=mysql_query(conn, mysql_get_total_cost.c_str());
		if(query_state!=0)
		{
			std::cout<<mysql_error(conn)<<std::endl<<std::endl;
		}

		res=mysql_store_result(conn);
		row=mysql_fetch_row(res);

		number_ip = number_ip_combobox->currentText().toUTF8();
		total_cost = boost::lexical_cast<std::string>(row[0]);
		credit_date = boost::lexical_cast<std::string>(credit_date_edit->text());
		description = description_text_area->text().toUTF8();

		mysql_free_result(res);

		std::string mysql_insert_new_onetime_credit = "INSERT INTO subscriber_transaction (subscriber_id, transaction_type, "
												"transaction_date, description, quantity)  "
												"VALUES ('"+subscriber_id_view_mode+"', 'Начисление', "
												"'"+credit_date+"', '"+service_name+"', '"+total_cost+"')";

		query_state=mysql_query(conn, mysql_insert_new_onetime_credit.c_str());
		if(query_state!=0)
		{
		   std::cout<<mysql_error(conn)<<std::endl<<std::endl;
		}

		mysql_close(conn);
/*
		subscriber_connected_table->clear();
		subscriber_connected_table->elementAt(0, 0)->addWidget(new Wt::WText(Wt::WString::fromUTF8("Услуга")));
		subscriber_connected_table->elementAt(0, 1)->addWidget(new Wt::WText(Wt::WString::fromUTF8("Номер/IP")));
		subscriber_connected_table->elementAt(0, 2)->addWidget(new Wt::WText(Wt::WString::fromUTF8("С")));
		subscriber_connected_table->elementAt(0, 3)->addWidget(new Wt::WText(Wt::WString::fromUTF8("По")));
		subscriber_connected_table->elementAt(0, 4)->addWidget(new Wt::WText(Wt::WString::fromUTF8("Количество")));
		subscriber_connected_table->elementAt(0, 5)->addWidget(new Wt::WText(Wt::WString::fromUTF8("Описание")));

		int row_number = 0;



		std::string mysql_service_table_data = "";

		if (operation_name == "create")
		{
			mysql_service_table_data = "select service, quantity, number_ip, description, date_since, date_by "
					  "from subscriber_connected_services where subscriber_connected_services.service_status = 'not_processed'";
		} else // operation_name == "edit"
		{
			mysql_service_table_data = "select service, quantity, number_ip, description, date_since, date_by "
					  "from subscriber_connected_services where subscriber_connected_services.subscriber_id = '"+subscriber_id_edit_mode+"'";
		}

		query_state=mysql_query(conn, mysql_service_table_data.c_str());
		if(query_state!=0)
		{
		   std::cout<<mysql_error(conn)<<std::endl<<std::endl;
		}
		res=mysql_store_result(conn);
		while((row=mysql_fetch_row(res))!=NULL)
		{
			row_number++;
			new Wt::WText(Wt::WString::fromUTF8(row[0]), subscriber_connected_table->elementAt(row_number, 0));
			new Wt::WText(Wt::WString::fromUTF8(row[2]), subscriber_connected_table->elementAt(row_number, 1));
			new Wt::WText(Wt::WString::fromUTF8(row[4]), subscriber_connected_table->elementAt(row_number, 2));
			new Wt::WText(Wt::WString::fromUTF8(row[5]), subscriber_connected_table->elementAt(row_number, 3));
			new Wt::WText(Wt::WString::fromUTF8(row[1]), subscriber_connected_table->elementAt(row_number, 4));
			new Wt::WText(Wt::WString::fromUTF8(row[3]), subscriber_connected_table->elementAt(row_number, 5));
		}
		subscriber_connected_table->refresh();
		mysql_free_result(res);
		mysql_close(conn);


*/
	}
	else
	{
	}

	delete dialog;
    }));

    dialog->show();
}


//initial debpt diablog window
extern void WtAccounts::subscriber_initial_debt_dialog()
{

	Wt::WMessageBox *messageBox;
	Wt::WTreeNode *selected_node; // operator* returns contents of an interator
	std::set<Wt::WTreeNode* > highlightedRows = ui->user_treeTable->tree()->selectedNodes();
	if (!highlightedRows.empty() && (subscriber_id_view_mode != ""))
	{




    Wt::WDialog *dialog = new Wt::WDialog(Wt::WString::fromUTF8("Начальный долг"));




    dialog->resize(400, 250);


    // payment quantity label and edit
    Wt::WLabel *payment_quantity_label = new Wt::WLabel(Wt::WString::fromUTF8("Долг:"),
    				       dialog->contents());
    payment_quantity_label->setStyleClass("col-lg-2 col-md-2 top_pad top_mar");

    Wt::WContainerWidget *payment_quantity_edit_container = new Wt::WContainerWidget(dialog->contents());
    payment_quantity_edit_container->setStyleClass(Wt::WString::fromUTF8("col-md-3 col-lg-3 top_mar"));
    payment_quantity_edit_container->setHtmlTagName("div");

    Wt::WLineEdit *payment_quantity_edit = new Wt::WLineEdit(payment_quantity_edit_container);
    payment_quantity_label->setBuddy(payment_quantity_edit);



    dialog->contents()->addStyleClass("form-group");


    Wt::WPushButton *ok = new Wt::WPushButton("OK", dialog->footer());
    ok->setDefault(true);


    Wt::WPushButton *cancel = new Wt::WPushButton("Cancel", dialog->footer());
    dialog->rejectWhenEscapePressed();

    int subscriber_initial_debt=0;

    mysql_init(&mysql);
    conn=mysql_real_connect(&mysql, server, user, password, database, 0, 0, 0);
    if(conn==NULL)
    {
    	std::cout<<mysql_error(&mysql)<<std::endl<<std::endl;
    }
    mysql_query(&mysql,"SET NAMES 'UTF8'");


    std::string  Aready_have_id="0"; //if we already hava data about dept then just get id and update
    std::string Sum_to_this_mouth = "SELECT transaction_id,quantity FROM account_database.subscriber_transaction where subscriber_id='"+subscriber_id_view_mode+"' and description='Начальный долг'";

    query_state = mysql_query(conn, Sum_to_this_mouth.c_str());
    if(query_state!=0)
    {
    	std::cout<<mysql_error(conn)<<std::endl<<std::endl;
    }
    res=mysql_store_result(conn);

    if ((row=mysql_fetch_row(res))!=NULL)
    {if (row[0]!=NULL){
    	Aready_have_id=row[0];
    	subscriber_initial_debt=std::atoi(row[1]);
       std::cout<<std::endl<<Aready_have_id<<std::endl;
    	mysql_free_result(res);
    }}
    payment_quantity_edit->setText(std::to_string(subscriber_initial_debt));
    //mysql_close(conn);



    // Accept the dialog
    ok->clicked().connect(std::bind([=] () {

	    dialog->accept();
    }));


    // Reject the dialog
    cancel->clicked().connect(dialog, &Wt::WDialog::reject);


    // Process the dialog result.
    dialog->finished().connect(std::bind([=] () {
	if (dialog->result() == Wt::WDialog::Accepted)
	{Wt::WMessageBox *messageBox;


          try {
		  std::string payment_quantity = boost::lexical_cast<std::string>(payment_quantity_edit->text());
		  std::string mysql_insert_new_payment_transaction="";

		  std::string current_month;
		  std::string current_year;
		  //check year
		  std::string ResulYearCombo="";
		  current_year=ui->year_combo_box->currentText().toUTF8();
		  //check month
		  int ResulMonthCombo_index;

		  std::string check_date_temp="";
		  ResulMonthCombo_index=ui->month_combo_box->currentIndex()+1;
		  check_date_temp=current_year+"-"+std::to_string(ResulMonthCombo_index)+"-1";

           if (Aready_have_id=="0"){
        	   std::string payment_date;
        	   std::string Sum_to_this_mouth = "SELECT date_since FROM account_database.subscriber where subscriber_id='"+subscriber_id_view_mode+"'";

        	   query_state = mysql_query(conn, Sum_to_this_mouth.c_str());
        	   if(query_state!=0)
        	   {
        		   std::cout<<mysql_error(conn)<<std::endl<<std::endl;
        	   }
        	   res=mysql_store_result(conn);

        	   if ((row=mysql_fetch_row(res))!=NULL)
        	   {   if (row[0]!=NULL){
        		   payment_date=row[0];}
        		   mysql_free_result(res);
        	   }

//007 fix


        	   //"'"+payment_date+"'
        std::cout<<std::endl<<"FIRST  " <<payment_quantity<<"  "<<payment_date<<std::endl;
		mysql_insert_new_payment_transaction = "INSERT INTO subscriber_transaction (subscriber_id, transaction_type, "
																"transaction_date, description, quantity)  "
																"VALUES ('"+subscriber_id_view_mode+"', 'Начисление', "
																"str_to_date('"+check_date_temp+"', '%Y-%m-%d') , 'Начальный долг', '"+payment_quantity+"')";
           }
           else {


        	   std::cout<<std::endl<<Aready_have_id<<"  "<<payment_quantity<<std::endl;
        	   mysql_insert_new_payment_transaction = "UPDATE subscriber_transaction SET quantity='"+payment_quantity+"',transaction_date=str_to_date('"+check_date_temp+"', '%Y-%m-%d')  WHERE transaction_id='"+Aready_have_id+"'";

           }
			query_state = mysql_query(conn, mysql_insert_new_payment_transaction.c_str());
			if(query_state!=0)
			{
			   std::cout<<mysql_error(conn)<<std::endl<<std::endl;
			}


	mysql_close(conn);
          } catch (const std::exception& e) {std::cout <<"Add or edit debt -> "<< e.what()<<std::endl;}
          }
	delete dialog;




    }));


    dialog->show();








    } else
    		{
    			messageBox = new Wt::WMessageBox(Wt::WString::fromUTF8("Ошибка"), Wt::WString::fromUTF8("Не выбран абонент"), Wt::Information, Wt::Yes | Wt::No);
    			messageBox->buttonClicked().connect(std::bind([=] () {
    			delete messageBox;
    			}));

    			messageBox->show();
    		}


}




// subscriber payment transaction dialog window
extern void WtAccounts::subscriber_payment_transaction_dialog()
{

	Wt::WMessageBox *messageBox;
	std::string changedSubscriberName = "";
	Wt::WTreeNode *selected_node; // operator* returns contents of an interator
	std::set<Wt::WTreeNode* > highlightedRows = ui->user_treeTable->tree()->selectedNodes();
	if (!highlightedRows.empty() && (subscriber_id_view_mode != ""))
	{




    Wt::WDialog *dialog = new Wt::WDialog(Wt::WString::fromUTF8("Оплата"));

    dialog->resize(700, 400);


    // payment quantity label and edit
    Wt::WLabel *payment_quantity_label = new Wt::WLabel(Wt::WString::fromUTF8("Сумма:"),
    				       dialog->contents());
    payment_quantity_label->setStyleClass("col-lg-2 col-md-2 top_pad top_mar");

    Wt::WContainerWidget *payment_quantity_edit_container = new Wt::WContainerWidget(dialog->contents());
    payment_quantity_edit_container->setStyleClass(Wt::WString::fromUTF8("col-md-3 col-lg-3 top_mar"));
    payment_quantity_edit_container->setHtmlTagName("div");

    Wt::WLineEdit *payment_quantity_edit = new Wt::WLineEdit(payment_quantity_edit_container);
    payment_quantity_label->setBuddy(payment_quantity_edit);



    // payment date label and date edit
    Wt::WLabel *payment_date_label = new Wt::WLabel(Wt::WString::fromUTF8("Дата оплаты:"),
    				       dialog->contents());
    payment_date_label->setStyleClass("col-lg-2 col-md-2 top_pad top_mar");

    Wt::WContainerWidget *payment_date_edit_container = new Wt::WContainerWidget(dialog->contents());
    payment_date_edit_container->setStyleClass(Wt::WString::fromUTF8("col-md-5 col-lg-5 top_mar"));
    payment_date_edit_container->setHtmlTagName("div");

    Wt::WDateEdit *payment_date_edit = new Wt::WDateEdit(payment_date_edit_container);
    payment_date_edit->setFormat("yyyy-MM-dd");
    payment_date_label->setBuddy(payment_date_edit);



    // payment type label and edit
    Wt::WLabel *payment_type_label = new Wt::WLabel(Wt::WString::fromUTF8("Тип оплаты:"),
    				       dialog->contents());
    payment_type_label->setStyleClass("col-lg-2 col-md-2 top_pad top_mar");

    Wt::WContainerWidget *payment_type_edit_container = new Wt::WContainerWidget(dialog->contents());
    payment_type_edit_container->setStyleClass(Wt::WString::fromUTF8("col-md-10 col-lg-10 top_mar"));
    payment_type_edit_container->setHtmlTagName("div");

    Wt::WLineEdit *payment_type_edit = new Wt::WLineEdit(payment_type_edit_container);
    payment_type_edit->setText(Wt::WString::fromUTF8("Наличные"));
    payment_type_label->setBuddy(payment_type_edit);



    // description label and text area
    Wt::WLabel *payment_description_label = new Wt::WLabel(Wt::WString::fromUTF8("Описание"),
    				       dialog->contents());
    payment_description_label->setStyleClass("col-lg-2 col-md-2 top_pad top_mar");

    Wt::WContainerWidget *payment_description_text_area_container = new Wt::WContainerWidget(dialog->contents());
    payment_description_text_area_container->setStyleClass(Wt::WString::fromUTF8("col-md-10 col-lg-10 top_mar"));
    payment_description_text_area_container->setHtmlTagName("div");

    Wt::WTextArea *payment_description_text_area = new Wt::WTextArea(payment_description_text_area_container);
    payment_description_text_area->setColumns(80);
    payment_description_text_area->setRows(3);
    payment_description_label->setBuddy(payment_description_text_area);



    // bank label and edit
    Wt::WLabel *bank_label = new Wt::WLabel(Wt::WString::fromUTF8("Банк:"),
    				       dialog->contents());
    bank_label->setStyleClass("col-lg-2 col-md-2 top_pad top_mar");

    Wt::WContainerWidget *bank_edit_container = new Wt::WContainerWidget(dialog->contents());
    bank_edit_container->setStyleClass(Wt::WString::fromUTF8("col-md-10 col-lg-10 top_mar"));
    bank_edit_container->setHtmlTagName("div");

    Wt::WLineEdit *bank_edit = new Wt::WLineEdit(bank_edit_container);
    // bank_edit->setText(Wt::WString::fromUTF8("Наличные"));
    bank_label->setBuddy(bank_edit);





    dialog->contents()->addStyleClass("form-group");


    Wt::WPushButton *ok = new Wt::WPushButton("OK", dialog->footer());
    ok->setDefault(true);


    Wt::WPushButton *cancel = new Wt::WPushButton("Cancel", dialog->footer());
    dialog->rejectWhenEscapePressed();



    // Accept the dialog
    ok->clicked().connect(std::bind([=] () {
	    dialog->accept();
    }));


    // Reject the dialog
    cancel->clicked().connect(dialog, &Wt::WDialog::reject);


    // Process the dialog result.
    dialog->finished().connect(std::bind([=] () {
	if (dialog->result() == Wt::WDialog::Accepted)
	{Wt::WMessageBox *messageBox;


		  int last_mouth_dept=0;
		  int chect_mouth_dept=0;
		  int sum_needTo_pay_thisM=0;

		  std::string payment_quantity = boost::lexical_cast<std::string>(payment_quantity_edit->text());
		  std::string payment_date = boost::lexical_cast<std::string>(payment_date_edit->text());
		  std::string payment_type = payment_type_edit->text().toUTF8();
		  std::string payment_description = payment_description_text_area->text().toUTF8();
		  std::string bank = bank_edit->text().toUTF8();

          			mysql_init(&mysql);
					conn=mysql_real_connect(&mysql, server, user, password, database, 0, 0, 0);
					if(conn==NULL)
					{
					    std::cout<<mysql_error(&mysql)<<std::endl<<std::endl;
					}
					mysql_query(&mysql,"SET NAMES 'UTF8'");

					std::string Sum_to_this_mouth = "SELECT sum(quantity) FROM account_database.subscriber_transaction WHERE subscriber_id='"+subscriber_id_view_mode+"' "
							"AND  month(transaction_date)=month('"+payment_date+"') AND year(transaction_date)=year('"+payment_date+"') AND transaction_type='Начисление'";

					query_state = mysql_query(conn, Sum_to_this_mouth.c_str());
					if(query_state!=0)
					{
						std::cout<<mysql_error(conn)<<std::endl<<std::endl;
					}
					res=mysql_store_result(conn);

					if ((row=mysql_fetch_row(res))!=NULL)
					{if (row[0]!=NULL){

						sum_needTo_pay_thisM=std::atoi(row[0]);
						std::cout<<sum_needTo_pay_thisM<<std::endl;
						mysql_free_result(res);







			std::string mysql_insert_new_payment_transaction = "INSERT INTO subscriber_transaction (subscriber_id, transaction_type, "
																"transaction_date, description, quantity)  "
																"VALUES ('"+subscriber_id_view_mode+"', 'Оплата', "
																"'"+payment_date+"', '"+payment_description+"', '"+payment_quantity+"')";

			query_state = mysql_query(conn, mysql_insert_new_payment_transaction.c_str());
			//query_state=mysql_query(conn, "select device, ip_address, description, date_since, date_by, "
			//							  "tariff_plan from ip_addresses where ip_addresses.ip_status = '"not_processed"'");
			if(query_state!=0)
			{
			   std::cout<<mysql_error(conn)<<std::endl<<std::endl;
			}


			mysql_close(conn);




				}else{mysql_close(conn);
	    			messageBox = new Wt::WMessageBox(Wt::WString::fromUTF8("Ошибка"), Wt::WString::fromUTF8("Некорректный месяц,отсутствуют услуги за которые требуются оплата"), Wt::Information, Wt::Yes | Wt::No);
	    			messageBox->buttonClicked().connect(std::bind([=] () {
	    			delete messageBox;
	    			}));

	    			messageBox->show();
	    		}}








	}
	else
	{
	}



	delete dialog;




    }));


    dialog->show();








    } else
    		{
    			messageBox = new Wt::WMessageBox(Wt::WString::fromUTF8("Ошибка"), Wt::WString::fromUTF8("Не выбран абонент"), Wt::Information, Wt::Yes | Wt::No);
    			messageBox->buttonClicked().connect(std::bind([=] () {
    			delete messageBox;
    			}));

    			messageBox->show();
    		}


}



// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%





// abaddon

// show dialog window where you can create new call tariffs
extern void WtAccounts::create_new_call_tariff_dialog(std::string operation_name,std::string operation_id)
{
    Wt::WDialog *dialog = new Wt::WDialog(Wt::WString::fromUTF8("Тарифы"));

    dialog->resize(800, 750);



    //description label and edit variables
    Wt::WLabel *description_label;
    Wt::WContainerWidget *description_edit_container;
    Wt::WLineEdit *description_edit;
	//country label and edit variables
	Wt::WLabel *country_label;
	Wt::WContainerWidget *country_edit_container;
	Wt::WLineEdit *country_edit;
	//country code label and edit variables
	Wt::WLabel *country_code_label;
	Wt::WContainerWidget *country_code_edit_container;
	Wt::WLineEdit *country_code_edit;
	//tariff date label and date edit variables
    Wt::WLabel *tariff_date_label;
    Wt::WContainerWidget *tariff_date_edit_container;
    Wt::WDateEdit *tariff_date_edit;
    // rounding label and edit variables
    Wt::WLabel *rounding_label;
    Wt::WContainerWidget *rounding_edit_container;
    Wt::WLineEdit *rounding_edit;
    // cost rounding label and edit variables
    Wt::WLabel *cost_rounding_label;
    Wt::WContainerWidget *cost_rounding_edit_container;
    Wt::WLineEdit *cost_rounding_edit;
    // operator label and edit varibales
    Wt::WLabel *operator_label;
    Wt::WContainerWidget *operator_edit_container;
    Wt::WLineEdit *operator_edit;
    //// plan label and edit varibles
    Wt::WLabel *plan_label;
   	Wt::WContainerWidget *plan_edit_container;
    Wt::WLineEdit *plan_edit;
    // add_text label and edit variables
    Wt::WLabel *add_text_label;
    Wt::WContainerWidget *add_text_edit_container;
    Wt::WLineEdit *add_text_edit ;

   if (operation_name != "Edit_price") {//hide containers if we edit zone price
	// dialog contents
    // description label and edit
    description_label = new Wt::WLabel(Wt::WString::fromUTF8("Описание:"),
    				       dialog->contents());
    description_label->setStyleClass("col-lg-3 col-md-3 top_pad top_mar");

    description_edit_container = new Wt::WContainerWidget(dialog->contents());
    description_edit_container->setStyleClass(Wt::WString::fromUTF8("col-md-9 col-lg-9 top_mar"));
    description_edit_container->setHtmlTagName("div");

    description_edit = new Wt::WLineEdit(description_edit_container);
    description_edit->setText(Wt::WString::fromUTF8(""));
    description_label->setBuddy(description_edit);



    // country label and edit
    country_label = new Wt::WLabel(Wt::WString::fromUTF8("Страна:"),
    				       dialog->contents());
    country_label->setStyleClass("col-lg-3 col-md-3 top_pad top_mar");

    country_edit_container = new Wt::WContainerWidget(dialog->contents());
    country_edit_container->setStyleClass(Wt::WString::fromUTF8("col-md-9 col-lg-9 top_mar"));
    country_edit_container->setHtmlTagName("div");

    country_edit = new Wt::WLineEdit(country_edit_container);
    country_edit->setText(Wt::WString::fromUTF8(""));
    country_label->setBuddy(country_edit);



    // country code label and edit
    country_code_label = new Wt::WLabel(Wt::WString::fromUTF8("Код страны:"),
    				       dialog->contents());
    country_code_label->setStyleClass("col-lg-3 col-md-3 top_pad top_mar");

    country_code_edit_container = new Wt::WContainerWidget(dialog->contents());
    country_code_edit_container->setStyleClass(Wt::WString::fromUTF8("col-md-9 col-lg-9 top_mar"));
    country_code_edit_container->setHtmlTagName("div");

    country_code_edit = new Wt::WLineEdit(country_code_edit_container);
    country_code_edit->setText(Wt::WString::fromUTF8(""));
    country_code_label->setBuddy(country_code_edit);

   }


    // tariff label and edit
    Wt::WLabel *tariff_label;
    Wt::WContainerWidget *tariff_edit_container;
    Wt::WLineEdit *tariff_edit;
    if (operation_name != "Edit_price") {//hide price if we edit text

    tariff_label = new Wt::WLabel(Wt::WString::fromUTF8("Тариф:"),
    				       dialog->contents());
    tariff_label->setStyleClass("col-lg-3 col-md-3 top_pad top_mar");

    tariff_edit_container = new Wt::WContainerWidget(dialog->contents());
    tariff_edit_container->setStyleClass(Wt::WString::fromUTF8("col-md-9 col-lg-9 top_mar"));
    tariff_edit_container->setHtmlTagName("div");

    tariff_edit = new Wt::WLineEdit(tariff_edit_container);
    tariff_edit->setText(Wt::WString::fromUTF8(""));
    tariff_label->setBuddy(tariff_edit);
    }


    // currency label and edit
    Wt::WLabel *currency_label = new Wt::WLabel(Wt::WString::fromUTF8("Валюта:"),
    				       dialog->contents());
    currency_label->setStyleClass("col-lg-3 col-md-3 top_pad top_mar");

    Wt::WContainerWidget *currency_edit_container = new Wt::WContainerWidget(dialog->contents());
    currency_edit_container->setStyleClass(Wt::WString::fromUTF8("col-md-9 col-lg-9 top_mar"));
    currency_edit_container->setHtmlTagName("div");

    Wt::WLineEdit *currency_edit = new Wt::WLineEdit(currency_edit_container);
    currency_edit->setText(Wt::WString::fromUTF8("KZT"));
    currency_label->setBuddy(currency_edit);



    Wt::WLineEdit *le;
    if (operation_name != "Edit_price") { //hide  all this containers if we edit zone price
    // tariff date label and date edit
    tariff_date_label = new Wt::WLabel(Wt::WString::fromUTF8("Дата тарифа:"),
    				       dialog->contents());
    tariff_date_label->setStyleClass("col-lg-3 col-md-3 top_pad top_mar");

    tariff_date_edit_container = new Wt::WContainerWidget(dialog->contents());
    tariff_date_edit_container->setStyleClass(Wt::WString::fromUTF8("col-md-9 col-lg-9 top_mar"));
    tariff_date_edit_container->setHtmlTagName("div");

    tariff_date_edit = new Wt::WDateEdit(tariff_date_edit_container);
    tariff_date_edit->setFormat("yyyy-MM-dd");
    tariff_date_label->setBuddy(tariff_date_edit);



    // rounding label and edit
    rounding_label = new Wt::WLabel(Wt::WString::fromUTF8("Округление:"),
    				       dialog->contents());
    rounding_label->setStyleClass("col-lg-3 col-md-3 top_pad top_mar");

    rounding_edit_container = new Wt::WContainerWidget(dialog->contents());
    rounding_edit_container->setStyleClass(Wt::WString::fromUTF8("col-md-9 col-lg-9 top_mar"));
    rounding_edit_container->setHtmlTagName("div");

    rounding_edit = new Wt::WLineEdit(rounding_edit_container);
    rounding_edit->setText(Wt::WString::fromUTF8(""));
    rounding_label->setBuddy(rounding_edit);



    // cost rounding label and edit
    cost_rounding_label = new Wt::WLabel(Wt::WString::fromUTF8("Округление стоимости:"),
    				       dialog->contents());
    cost_rounding_label->setStyleClass("col-lg-3 col-md-3 top_pad top_mar");

    cost_rounding_edit_container = new Wt::WContainerWidget(dialog->contents());
    cost_rounding_edit_container->setStyleClass(Wt::WString::fromUTF8("col-md-9 col-lg-9 top_mar"));
    cost_rounding_edit_container->setHtmlTagName("div");

    cost_rounding_edit = new Wt::WLineEdit(cost_rounding_edit_container);
    cost_rounding_edit->setText(Wt::WString::fromUTF8(""));
    cost_rounding_label->setBuddy(cost_rounding_edit);



    // operator label and edit
    operator_label = new Wt::WLabel(Wt::WString::fromUTF8("Оператор:"),
    		dialog->contents());
    operator_label->setStyleClass("col-lg-3 col-md-3 top_pad top_mar");

    operator_edit_container = new Wt::WContainerWidget(dialog->contents());
    operator_edit_container->setStyleClass(Wt::WString::fromUTF8("col-md-9 col-lg-9 top_mar"));
    operator_edit_container->setHtmlTagName("div");

    operator_edit = new Wt::WLineEdit(operator_edit_container);
    operator_edit->setText(Wt::WString::fromUTF8("КазТрансКом"));
    operator_label->setBuddy(operator_edit);

    // plan label and edit
    plan_label = new Wt::WLabel(Wt::WString::fromUTF8("План:"),
    				       dialog->contents());
    plan_label->setStyleClass("col-lg-3 col-md-3 top_pad top_mar");

    plan_edit_container = new Wt::WContainerWidget(dialog->contents());
    plan_edit_container->setStyleClass(Wt::WString::fromUTF8("col-md-9 col-lg-9 top_mar"));
    plan_edit_container->setHtmlTagName("div");



    plan_edit = new Wt::WLineEdit(plan_edit_container);
   plan_edit->setText(Wt::WString::fromUTF8("физ.лица"));
  ///plan_edit->setText(Wt::WString::fromUTF8(FAKE));
    plan_label->setBuddy(plan_edit);




    // add_text label and edit
    add_text_label = new Wt::WLabel(Wt::WString::fromUTF8("Текст начисления:"),
    				       dialog->contents());
    add_text_label->setStyleClass("col-lg-3 col-md-3 top_pad top_mar strong");

    add_text_edit_container = new Wt::WContainerWidget(dialog->contents());
    add_text_edit_container->setStyleClass(Wt::WString::fromUTF8("col-md-9 col-lg-9 top_mar"));
    add_text_edit_container->setHtmlTagName("div");

    // Set options for email address suggestions:
    Wt::WSuggestionPopup::Options contactOptions;
   contactOptions.highlightBeginTag = "<span class=\"highlight\">";
   contactOptions.highlightEndTag = "</span>";
   contactOptions.whitespace = " \\n";
   contactOptions.wordSeparators = "-., \"@\\n;";

   Wt::WSuggestionPopup *sp = new Wt::WSuggestionPopup(
		   Wt::WSuggestionPopup::generateMatcherJS(contactOptions),
		   Wt::WSuggestionPopup::generateReplacerJS(contactOptions),
		   add_text_edit_container);

    le = new Wt::WLineEdit(add_text_edit_container);
    le->setEmptyText("");
    sp->forEdit(le);
    add_text_label->setBuddy(le);

    // Populate the underlying model with suggestions:
    sp->addSuggestion(Wt::WString::fromUTF8("Международные переговоры"));
    sp->addSuggestion(Wt::WString::fromUTF8("Межгород"));
    sp->addSuggestion(Wt::WString::fromUTF8("Мобильная связь"));
    sp->addSuggestion(Wt::WString::fromUTF8("За услуги"));

 //  add_text_edit = new Wt::WLineEdit(add_text_edit_container);
 //  add_text_edit->setText(Wt::WString::fromUTF8(""));
 //  add_text_label->setBuddy(add_text_edit);


    }


    // add_text label and edit
     Wt::WLabel *add_zone_label = new Wt::WLabel(Wt::WString::fromUTF8("Зона:"),
           				       dialog->contents());
     add_zone_label->setStyleClass("col-lg-3 col-md-3 top_pad top_mar");

     Wt::WContainerWidget *add_zone_edit_container = new Wt::WContainerWidget(dialog->contents());
     add_zone_edit_container->setStyleClass(Wt::WString::fromUTF8("col-md-9 col-lg-9 top_mar"));
     add_zone_edit_container->setHtmlTagName("div");

     Wt::WLineEdit *add_zone_edit = new Wt::WLineEdit(add_zone_edit_container);
     add_zone_edit->setText(Wt::WString::fromUTF8(""));
     add_zone_label->setBuddy(add_zone_edit);




    dialog->contents()->addStyleClass("form-group");


    Wt::WPushButton *ok = new Wt::WPushButton("OK", dialog->footer());
    ok->setDefault(true);


    Wt::WPushButton *cancel = new Wt::WPushButton("Cancel", dialog->footer());
    dialog->rejectWhenEscapePressed();



    // Accept the dialog
    ok->clicked().connect(std::bind([=] () {
	    dialog->accept();
    }));


    // Reject the dialog
    cancel->clicked().connect(dialog, &Wt::WDialog::reject);

    std::string mysql_get_ip_addressesQ = "";
    if (operation_name == "Edit_text")
    {
    	mysql_init(&mysql);
    	conn=mysql_real_connect(&mysql, server, user, password, database, 0, 0, 0);
    	if(conn==NULL)
    			{
    			    std::cout<<mysql_error(&mysql)<<std::endl<<std::endl;
    			}
    			mysql_query(&mysql,"SET NAMES 'UTF8'");


   mysql_get_ip_addressesQ = "SELECT * FROM account_database.call_tariff "
		   "WHERE tariff_id='"+ operation_id +"'";


	query_state=mysql_query(conn, mysql_get_ip_addressesQ.c_str());
		if(query_state!=0)
		{
			std::cout<<mysql_error(conn)<<std::endl<<std::endl;
		}
	res=mysql_store_result(conn);
	if((row=mysql_fetch_row(res))!=NULL){

		    add_zone_edit->setText(Wt::WString::fromUTF8(row[1]));
		    description_edit->setText(Wt::WString::fromUTF8(row[2]));
			country_edit->setText(Wt::WString::fromUTF8(row[3]));
			country_code_edit->setText(Wt::WString::fromUTF8(row[4]));
			tariff_edit->setText(Wt::WString::fromUTF8(row[5]));
			currency_edit->setText(Wt::WString::fromUTF8(row[6]));

			if (Wt::WString::fromUTF8(row[7])!="0000-00-00") {
			tariff_date_edit->setText(Wt::WString::fromUTF8(row[7]));
			std::cout<<"DAAAAAAAAAATEEEEEEEEE"<<row[7]<<std::endl;}
			rounding_edit->setText(Wt::WString::fromUTF8(row[8]));
			cost_rounding_edit->setText(Wt::WString::fromUTF8(row[9]));

			operator_edit->setText(Wt::WString::fromUTF8(row[10]));
			plan_edit->setText(Wt::WString::fromUTF8(row[11]));
			le->setText(Wt::WString::fromUTF8(row[12]));
			//add_text_edit->setText(Wt::WString::fromUTF8(row[12]));

	}
	mysql_free_result(res);
	mysql_close(conn);

    }

    if (operation_name == "Edit_price")
       {
       	mysql_init(&mysql);
       	conn=mysql_real_connect(&mysql, server, user, password, database, 0, 0, 0);
       	if(conn==NULL)
       			{
       			    std::cout<<mysql_error(&mysql)<<std::endl<<std::endl;
       			}
       			mysql_query(&mysql,"SET NAMES 'UTF8'");


      mysql_get_ip_addressesQ = "SELECT * FROM account_database.call_tariff "
   		   "WHERE zone_description='"+ operation_id +"'";


   	query_state=mysql_query(conn, mysql_get_ip_addressesQ.c_str());
   		if(query_state!=0)
   		{
   			std::cout<<mysql_error(conn)<<std::endl<<std::endl;
   		}
   	res=mysql_store_result(conn);
   	if((row=mysql_fetch_row(res))!=NULL){




   		    add_zone_edit->setText(Wt::WString::fromUTF8(row[1]));
   		//	tariff_edit->setText(Wt::WString::fromUTF8(row[5]));
   			currency_edit->setText(Wt::WString::fromUTF8(row[6]));

   		//	tariff_date_edit->setText(Wt::WString::fromUTF8(row[7]));

   			//rounding_edit->setText(Wt::WString::fromUTF8());
   		//	cost_rounding_edit->setText(Wt::WString::fromUTF8(row[9]));
   			//operator_edit->setText(Wt::WString::fromUTF8(row[10]));
   		//	plan_edit->setText(Wt::WString::fromUTF8(row[11]));

   	}
   	mysql_free_result(res);
   	mysql_close(conn);

       }


    // Process the dialog result.
    dialog->finished().connect(std::bind([=] () {
	if (dialog->result() == Wt::WDialog::Accepted)
	{
		std::string description = "";
		std::string country = "";
		std::string country_code = "";
		std::string tariff = "";
		std::string currency = "";
		std::string tariff_date = "";
		std::string rounding = "";
		std::string cost_rounding = "";
		std::string operator_ = "";
		std::string plan = "";
		std::string add_text = "";
		std::string zone = "";

		mysql_init(&mysql);
		conn=mysql_real_connect(&mysql, server, user, password, database, 0, 0, 0);
		if(conn==NULL)
		{
		    std::cout<<mysql_error(&mysql)<<std::endl<<std::endl;
		}
		mysql_query(&mysql,"SET NAMES 'UTF8'");




		//if (operation_name != "Edit_text") {tariff = boost::lexical_cast<std::string>(tariff_edit->text());}

		if(operation_name != "Edit_price"){
		tariff = boost::lexical_cast<std::string>(tariff_edit->text());
		description = description_edit->text().toUTF8();
		country = country_edit->text().toUTF8();
		country_code = boost::lexical_cast<std::string>(country_code_edit->text());
		tariff_date = boost::lexical_cast<std::string>(tariff_date_edit->text());
		rounding = boost::lexical_cast<std::string>(rounding_edit->text());
		cost_rounding = boost::lexical_cast<std::string>(cost_rounding_edit->text());
		operator_ = operator_edit->text().toUTF8();
		plan = plan_edit->text().toUTF8();
		add_text = le->text().toUTF8();}
				//add_text_edit->text().toUTF8();}

		zone = add_zone_edit->text().toUTF8();
		currency = currency_edit->text().toUTF8();

		//RANDOM
				/*
				int iSecret, iGuess;
					// initialize random seed:
					srand (time(NULL));

				 std::string FAKE[5]="";

					// generate secret number between 1 and 10:

				 for (int i=0;i<5;i++){

				  iSecret = rand() % 60 + 60;
				  char ds=static_cast<char>(iSecret);
				  FAKE[i]+=ds;

				  iSecret = rand() % 9346 + 4357;
				  FAKE[i]+=std::to_string(iSecret);
				  iSecret = rand() % 60 + 60;

				  ds=static_cast<char>(iSecret);
			      FAKE[i]+=ds;
			      iSecret = rand() % 60 + 60;
			      ds=static_cast<char>(iSecret);
			      FAKE[i]+=ds;
				 } */
		//END RANDOM


		std::string mysql_insert_create_call_tariff;
		 if (operation_name == "Add")
		    {
		mysql_insert_create_call_tariff = "INSERT INTO account_database.call_tariff "
					"(description, country, code, tariff, currency, "
					"tariff_date, round, round_price, operator, plan, add_text,zone_description) "
					"values ('"+ description +"', '"+ country +"', '"+ country_code +"', "
					"'"+ tariff +"', '"+ currency +"', '"+ tariff_date +"', '"+ rounding +"', "
					"'"+ cost_rounding +"', '"+ operator_ +"', '"+ plan +"', '"+ add_text +"','"+ zone +"')";
		    }
		 //
		 if (operation_name == "Edit_text")
		 		    {std::cout<<std::endl<<"selected_service= selected_node->  "<<currency<<std::endl;
		 mysql_insert_create_call_tariff = "UPDATE account_database.call_tariff SET "
		 		"tariff='"+ tariff +"',description='"+ description +"', country='"+ country +"', code='"+ country_code +"', currency='"+ currency +"', "
		 		"tariff_date='"+ tariff_date +"', round='"+ rounding +"', round_price='"+ cost_rounding +"', "
		 	     "operator='"+ operator_ +"', plan='"+ plan +"', add_text='"+ add_text +"',zone_description='"+ zone +"' "
		 		" WHERE tariff_id='"+ operation_id +"'";
		 		    }


		 if (operation_name == "Edit_price")
		 		 		    {
		 		 mysql_insert_create_call_tariff = " UPDATE account_database.call_tariff "
		 				 "SET zone_description='"+ zone +"',currency='"+ currency +"' WHERE zone_description='"+ operation_id +"'";
		 		 		    }






		query_state=mysql_query(conn, mysql_insert_create_call_tariff.c_str());
		if(query_state!=0)
		{
			std::cout<<mysql_error(conn)<<std::endl<<std::endl;
		}


		call_tariff_table->clear();
		call_tariff_table->elementAt(0, 0)->addWidget(new Wt::WText(Wt::WString::fromUTF8("Зона")));
		call_tariff_table->elementAt(0, 1)->addWidget(new Wt::WText(Wt::WString::fromUTF8("Описание")));
		call_tariff_table->elementAt(0, 2)->addWidget(new Wt::WText(Wt::WString::fromUTF8("Страна")));
		call_tariff_table->elementAt(0, 3)->addWidget(new Wt::WText(Wt::WString::fromUTF8("Код")));
		call_tariff_table->elementAt(0, 4)->addWidget(new Wt::WText(Wt::WString::fromUTF8("Тариф")));
		call_tariff_table->elementAt(0, 5)->addWidget(new Wt::WText(Wt::WString::fromUTF8("Валюта")));
		call_tariff_table->elementAt(0, 6)->addWidget(new Wt::WText(Wt::WString::fromUTF8("Дата")));
		call_tariff_table->elementAt(0, 7)->addWidget(new Wt::WText(Wt::WString::fromUTF8("Округление")));
		call_tariff_table->elementAt(0, 8)->addWidget(new Wt::WText(Wt::WString::fromUTF8("Округление стоимости")));
		call_tariff_table->elementAt(0, 9)->addWidget(new Wt::WText(Wt::WString::fromUTF8("Оператор")));
		call_tariff_table->elementAt(0, 10)->addWidget(new Wt::WText(Wt::WString::fromUTF8("План")));
		call_tariff_table->elementAt(0, 11)->addWidget(new Wt::WText(Wt::WString::fromUTF8("Текст начисления")));
		call_tariff_table->elementAt(0, 12)->addWidget(new Wt::WText(Wt::WString::fromUTF8("id")));
		int row_number = 0;



		std::string mysql_call_tariff_table_data = "SELECT * FROM account_database.call_tariff ORDER BY RAND() LIMIT 100";

		query_state=mysql_query(conn, mysql_call_tariff_table_data.c_str());
		if(query_state!=0)
		{
		   std::cout<<mysql_error(conn)<<std::endl<<std::endl;
		}
		res=mysql_store_result(conn);
		while((row=mysql_fetch_row(res))!=NULL)
		{
			row_number++;
			new Wt::WText(Wt::WString::fromUTF8(row[1]), call_tariff_table->elementAt(row_number, 0));
			new Wt::WText(Wt::WString::fromUTF8(row[2]), call_tariff_table->elementAt(row_number, 1));
			new Wt::WText(Wt::WString::fromUTF8(row[3]), call_tariff_table->elementAt(row_number, 2));
			new Wt::WText(Wt::WString::fromUTF8(row[4]), call_tariff_table->elementAt(row_number, 3));
			new Wt::WText(Wt::WString::fromUTF8(row[5]), call_tariff_table->elementAt(row_number, 4));
			new Wt::WText(Wt::WString::fromUTF8(row[6]), call_tariff_table->elementAt(row_number, 5));
			new Wt::WText(Wt::WString::fromUTF8(row[7]), call_tariff_table->elementAt(row_number, 6));
			new Wt::WText(Wt::WString::fromUTF8(row[8]), call_tariff_table->elementAt(row_number, 7));
			new Wt::WText(Wt::WString::fromUTF8(row[9]), call_tariff_table->elementAt(row_number, 8));
			new Wt::WText(Wt::WString::fromUTF8(row[10]), call_tariff_table->elementAt(row_number, 9));
			new Wt::WText(Wt::WString::fromUTF8(row[11]), call_tariff_table->elementAt(row_number, 10));
			new Wt::WText(Wt::WString::fromUTF8(row[12]), call_tariff_table->elementAt(row_number, 11));
			new Wt::WText(Wt::WString::fromUTF8(row[0]), call_tariff_table->elementAt(row_number, 12));
		}
		call_tariff_table->refresh();
		mysql_free_result(res);
		mysql_close(conn);
	}

	delete dialog;
    }));

    dialog->show();
}

//selete abadon
extern void WtAccounts::create_new_select_tariff_dialog_S(std::string operation_name){

	Wt::WDialog *dialog_edit_tariff;

	Wt::WLineEdit *Tarif_search_edit_edit;
	Wt::WPushButton *Tarif_search_button_edit;
	 if (operation_name == "Edit_text") {
	   dialog_edit_tariff = new Wt::WDialog(Wt::WString::fromUTF8("Редактировать данные"));
	 }else {dialog_edit_tariff = new Wt::WDialog(Wt::WString::fromUTF8("Редактировать Зоны"));}

	    dialog_edit_tariff->resize(600, 600);



	    // container for table with data about ip address
	    Wt::WContainerWidget *call_tariff_table_container_edit = new Wt::WContainerWidget(dialog_edit_tariff->contents());
	    //call_tariff_table_container->setStyleClass(Wt::WString::fromUTF8("col-md-9 col-lg-9 top_mar"));
	    call_tariff_table_container_edit->setHtmlTagName("div");
	    call_tariff_table_container_edit->setWidth(Wt::WLength("100%"));
	    call_tariff_table_container_edit->setHeight(Wt::WLength("100%"));
	    call_tariff_table_container_edit->setOverflow(Wt::WContainerWidget::Overflow::OverflowAuto, Wt::Orientation::Vertical);





	    Tarif_search_button_edit = new Wt::WPushButton(dialog_edit_tariff->footer());
	   // Tarif_search_button_edit->setId("user_search_button");
	    Tarif_search_button_edit->setStyleClass(Wt::WString::fromUTF8("with-label btn btn-default btn btn-default with-label"));
	    Tarif_search_button_edit->setInline(0);
	    Tarif_search_button_edit->setEmptyText(Wt::WString::fromUTF8(""));
	    Tarif_search_button_edit->setText(Wt::WString::fromUTF8("Поиск"));
	    Tarif_search_button_edit->setLink(Wt::WLink(""));

	    Tarif_search_edit_edit = new Wt::WLineEdit(dialog_edit_tariff->footer());
	    Tarif_search_edit_edit->setEmptyText(Wt::WString::fromUTF8(" "));


		mysql_init(&mysql);
		conn=mysql_real_connect(&mysql, server, user, password, database, 0, 0, 0);

		if(conn==NULL)
		{
		    std::cout<<mysql_error(&mysql)<<std::endl<<std::endl;
		}

		mysql_query(&mysql,"SET NAMES 'UTF8'");


		std::string temp1_text;
		std::string temp2_text;
		std::string temp3_text;
		std::string tempid_text;
	    Wt::WTreeTable *treeTable;
		treeTable = new Wt::WTreeTable(call_tariff_table_container_edit);
	    //treeTable->resize(650, 300);
	    treeTable->setStyleClass(Wt::WString::fromUTF8("Wt-treetable col-lg-12 col-md-12"));
	    treeTable->tree()->setSelectionMode(Wt::SingleSelection);

	    if (operation_name == "Edit_text") {

	    	temp1_text="Описание";
	    	temp2_text="id";
	    	temp3_text="Коды и страны";
	    	tempid_text="Код";
	    }else {
	    	temp1_text="Описание";
	    	temp2_text="Зоны и страны";
	    	temp3_text="Зоны";
	    }
	    treeTable->addColumn(Wt::WString::fromUTF8(temp1_text), 300);
	    if (operation_name == "Edit_text") {treeTable->addColumn(Wt::WString::fromUTF8(tempid_text),150);}

	    Wt::WTreeTableNode *tree_root;
	    if (operation_name == "Edit_text") {
		tree_root = new Wt::WTreeTableNode(Wt::WString::fromUTF8(temp2_text),0);}
	    else
	    tree_root = new Wt::WTreeTableNode(Wt::WString::fromUTF8(temp2_text));
	    treeTable->setTreeRoot(tree_root, Wt::WString::fromUTF8(temp3_text));

	    Wt::WTreeTableNode *tree_node;

	    std::string mysql_get_ip_briffdata_for_select= "";

	// add node form mysql table
	    if (operation_name == "Edit_text")
	    {
	    	mysql_get_ip_briffdata_for_select = "SELECT tariff_id,description,code FROM account_database.call_tariff LIMIT 100";
	    } else // operation_name == "edit"
	    {
	    	mysql_get_ip_briffdata_for_select = "SELECT zone_description,description FROM account_database.call_tariff GROUP BY zone_description LIMIT 100";
	    }
	    query_state=mysql_query(conn, mysql_get_ip_briffdata_for_select.c_str());
	    if(query_state!=0)
	    {
	    	std::cout<<mysql_error(conn)<<std::endl<<std::endl;
	    }
	    res=mysql_store_result(conn);
	    std::cout<<"MySQL Values in the amaDB Table.13"<<std::endl<<std::endl;
	    while((row=mysql_fetch_row(res))!=NULL)
	    {

	    	//Dont show in selecet menu if there is no zone or code
	    	if (Wt::WString::fromUTF8(row[0])!=""){
	    	tree_node  = new Wt::WTreeTableNode(Wt::WString::fromUTF8(row[0]), 0, tree_root);
	    	tree_node ->setColumnWidget(1, new Wt::WText(Wt::WString::fromUTF8(row[1])));
	    	if (operation_name == "Edit_text")
	    		    			    	{tree_node ->setColumnWidget(2, new Wt::WText(Wt::WString::fromUTF8(row[2])));}
	    	}
	    	//tree_node ->setColumnWidget(2, new Wt::WText(Wt::WString::fromUTF8(row[2])));}
	    }

		mysql_free_result(res);
		mysql_close(conn);

		tree_root->expand();



	    Wt::WPushButton *ok = new Wt::WPushButton(Wt::WString::fromUTF8("Редактировать"), dialog_edit_tariff->footer());
	    ok->setDefault(true);


	    Wt::WPushButton *cancel = new Wt::WPushButton("Cancel", dialog_edit_tariff->footer());
	    dialog_edit_tariff->rejectWhenEscapePressed();


	    Tarif_search_button_edit->clicked().connect(std::bind([=] () {
try {
	    	Wt::WTreeTableNode *tree_root;

	    	tree_root = new Wt::WTreeTableNode(Wt::WString::fromUTF8(temp2_text));
	    	treeTable->setTreeRoot(tree_root, Wt::WString::fromUTF8(temp3_text));

	    	Wt::WTreeTableNode *tree_node;

	    	std::string mysql_get_ip_briffdata_for_select= "";
	    	std::string tarif_search_text=Tarif_search_edit_edit->text().toUTF8();

	    	mysql_init(&mysql);
	    	conn=mysql_real_connect(&mysql, server, user, password, database, 0, 0, 0);

	    	if(conn==NULL)
	    	{
	    		std::cout<<mysql_error(&mysql)<<std::endl<<std::endl;
	    	}

	    	mysql_query(&mysql,"SET NAMES 'UTF8'");


	    	// add node form mysql table
	    	if (operation_name == "Edit_text")
	    	{
	    		mysql_get_ip_briffdata_for_select = "SELECT tariff_id,description,code FROM account_database.call_tariff WHERE locate('"+ tarif_search_text +"',code)>0 OR locate('"+ tarif_search_text +"',description)>0 OR locate('"+ tarif_search_text +"',zone_description)>0 LIMIT 20";
	    	} else // operation_name == "edit"
	    	{
	    		mysql_get_ip_briffdata_for_select = "SELECT zone_description,description FROM account_database.call_tariff WHERE locate('"+ tarif_search_text +"',zone_description)>0 GROUP BY zone_description LIMIT 10";
	    	}
	    	query_state=mysql_query(conn, mysql_get_ip_briffdata_for_select.c_str());
	    	if(query_state!=0)
	    	{
	    		std::cout<<mysql_error(conn)<<std::endl<<std::endl;
	    	}
	    	res=mysql_store_result(conn);
	    	std::cout<<"MySQL Values in the amaDB Table.14"<<std::endl<<std::endl;

	    	while((row=mysql_fetch_row(res))!=NULL)
	    	{

	    		//Dont show in selecet menu if there is no zone or code
	    		if (Wt::WString::fromUTF8(row[0])!=""){
	    			tree_node  = new Wt::WTreeTableNode(Wt::WString::fromUTF8(row[0]), 0, tree_root);
	    			tree_node ->setColumnWidget(1, new Wt::WText(Wt::WString::fromUTF8(row[1])));
	    			if (operation_name == "Edit_text")
	    			    	{tree_node ->setColumnWidget(2, new Wt::WText(Wt::WString::fromUTF8(row[2])));}
	    			}
	    		//tree_node ->setColumnWidget(2, new Wt::WText(Wt::WString::fromUTF8(row[2])));}
	    	}

	    	mysql_free_result(res);
	    	mysql_close(conn);
	    	tree_root->expand();
} catch (const std::exception& e) {std::cout <<"Search in code tariff error -> "<< e.what()<<std::endl;}
	    }));



	    // Accept the dialog_edit_tariff
	    ok->clicked().connect(std::bind([=] () {
		    dialog_edit_tariff->accept();
	    }));


	    // Reject the dialog_edit_tariff
	    cancel->clicked().connect(dialog_edit_tariff, &Wt::WDialog::reject);


	    // Process the dialog_edit_tariff result.
	    dialog_edit_tariff->finished().connect(std::bind([=] () {
		if (dialog_edit_tariff->result() == Wt::WDialog::Accepted)
		{


			mysql_init(&mysql);
			conn=mysql_real_connect(&mysql, server, user, password, database, 0, 0, 0);
			/*
			if(conn==NULL)
			{
			    std::cout<<mysql_error(&mysql)<<std::endl<<std::endl;
			}
			 */
			mysql_query(&mysql,"SET NAMES 'UTF8'");



			std::string mysql_delete_ip_address = "";
			std::string selected_service = "";

			Wt::WTreeNode *selected_node; // operator* returns contents of an interator
			std::set<Wt::WTreeNode* > highlightedRows = treeTable->tree()->selectedNodes();
			if (!highlightedRows.empty())
			{
				for (std::set<Wt::WTreeNode* >::iterator i = highlightedRows.begin(); i != highlightedRows.end(); ++i)
				{
					selected_node = *i;
				}

				selected_service= selected_node->label()->text().toUTF8();

				mysql_close(conn);


				create_new_call_tariff_dialog(operation_name,selected_service);
			}




		}
		else
		{
		}

		delete dialog_edit_tariff;
	    }));

	    dialog_edit_tariff->show();










}







//abadon1
// show dialog window where you manage call tariffs (create)
extern void WtAccounts::manage_new_call_tariff_dialog()
{
Wt::WLineEdit *Tarif_search_edit;
Wt::WPushButton *Tarif_search_button;


    Wt::WDialog *dialog = new Wt::WDialog(Wt::WString::fromUTF8("Тарифы на вызовы"));

    dialog->resize(1550, 850);



    Tarif_search_button = new Wt::WPushButton(dialog->footer());
   // Tarif_search_button->setId("user_search_button");
    Tarif_search_button->setStyleClass(Wt::WString::fromUTF8("with-label btn btn-default btn btn-default with-label"));
    Tarif_search_button->setInline(0);
    Tarif_search_button->setEmptyText(Wt::WString::fromUTF8(""));
    Tarif_search_button->setText(Wt::WString::fromUTF8("Поиск"));
    Tarif_search_button->setLink(Wt::WLink(""));

    Tarif_search_edit = new Wt::WLineEdit(dialog->footer());
        //Tarif_search_edit->setId("Tarif_search_edit");
       // Tarif_search_edit->setStyleClass(Wt::WString::fromUTF8("form-control form-control"));
       // Tarif_search_edit->setInline(0);
        Tarif_search_edit->setEmptyText(Wt::WString::fromUTF8(" "));

    // srevice top buttons
    Wt::WPushButton *save_exit_button = new Wt::WPushButton(Wt::WString::fromUTF8("Сохранить и закрыть"), dialog->contents());
    save_exit_button->setStyleClass(Wt::WString::fromUTF8("btn btn-default with-label col-md-3 col-lg-3"));

    Wt::WPushButton *add_service_button = new Wt::WPushButton(Wt::WString::fromUTF8("Добавить"), dialog->contents());
    add_service_button->setStyleClass(Wt::WString::fromUTF8("btn btn-default with-label col-md-3 col-lg-3"));

    //edit text
    Wt::WPushButton *edit_service_text_button = new Wt::WPushButton(Wt::WString::fromUTF8("Изменить данные"), dialog->contents());
    edit_service_text_button->setStyleClass(Wt::WString::fromUTF8("btn btn-default with-label col-md-3 col-lg-3"));
    //edit zone
    Wt::WPushButton *edit_service_price_button = new Wt::WPushButton(Wt::WString::fromUTF8("Редактировать Зоны "), dialog->contents());
    edit_service_price_button->setStyleClass(Wt::WString::fromUTF8("btn btn-default with-label col-md-3 col-lg-3"));



	add_service_button->clicked().connect(boost::bind(&WtAccounts::create_new_call_tariff_dialog, this,"Add",""));

	edit_service_price_button->clicked().connect(boost::bind(&WtAccounts::create_new_select_tariff_dialog_S, this,"Edit_price" ));
	edit_service_text_button->clicked().connect(boost::bind(&WtAccounts::create_new_select_tariff_dialog_S, this,"Edit_text"));


	//delete_service_button->clicked().connect(boost::bind(&WtAccounts::delete_service_dialog, this, operation_name));



	mysql_init(&mysql);
	conn=mysql_real_connect(&mysql, server, user, password, database, 0, 0, 0);
	if(conn==NULL)
	{
	    std::cout<<mysql_error(&mysql)<<std::endl<<std::endl;
	}
	mysql_query(&mysql,"SET NAMES 'UTF8'");


	// container for table with data about ip address
    Wt::WContainerWidget *call_tariff_table_container = new Wt::WContainerWidget(dialog->contents());
    //call_tariff_table_container->setStyleClass(Wt::WString::fromUTF8("col-md-9 col-lg-9 top_mar"));
    call_tariff_table_container->setHtmlTagName("div");
    call_tariff_table_container->setWidth(Wt::WLength("100%"));
    call_tariff_table_container->setHeight(Wt::WLength("650px"));
    call_tariff_table_container->setOverflow(Wt::WContainerWidget::Overflow::OverflowAuto, Wt::Orientation::Vertical);

	// table with data about ip address
	call_tariff_table = new Wt::WTable(call_tariff_table_container);
	call_tariff_table->setHeaderCount(1);
	call_tariff_table->setWidth(Wt::WLength("100%"));
	//call_tariff_table->setHeight(Wt::WLength("50%"));
	//call_tariff_table->setHeight(Wt::WLength("100px"));
	//call_tariff_table->resize(1000, 100);
	//call_tariff_table


	call_tariff_table->setHeaderCount(1);

	//call_tariff_table->resize();
	call_tariff_table->elementAt(0, 0)->addWidget(new Wt::WText(Wt::WString::fromUTF8("Зона")));
	call_tariff_table->elementAt(0, 1)->addWidget(new Wt::WText(Wt::WString::fromUTF8("Описание")));
    call_tariff_table->elementAt(0, 2)->addWidget(new Wt::WText(Wt::WString::fromUTF8("Страна")));
	call_tariff_table->elementAt(0, 3)->addWidget(new Wt::WText(Wt::WString::fromUTF8("Код")));
	call_tariff_table->elementAt(0, 4)->addWidget(new Wt::WText(Wt::WString::fromUTF8("Тариф")));
	call_tariff_table->elementAt(0, 5)->addWidget(new Wt::WText(Wt::WString::fromUTF8("Валюта")));
	call_tariff_table->elementAt(0, 6)->addWidget(new Wt::WText(Wt::WString::fromUTF8("Дата")));
	call_tariff_table->elementAt(0, 7)->addWidget(new Wt::WText(Wt::WString::fromUTF8("Округление")));
	call_tariff_table->elementAt(0, 8)->addWidget(new Wt::WText(Wt::WString::fromUTF8("Округление стоимости")));
	call_tariff_table->elementAt(0, 9)->addWidget(new Wt::WText(Wt::WString::fromUTF8("Оператор")));
	call_tariff_table->elementAt(0, 10)->addWidget(new Wt::WText(Wt::WString::fromUTF8("План")));
	call_tariff_table->elementAt(0, 11)->addWidget(new Wt::WText(Wt::WString::fromUTF8("Текст начисления")));
	call_tariff_table->elementAt(0, 12)->addWidget(new Wt::WText(Wt::WString::fromUTF8("id")));
	int row_number = 0;



	std::string mysql_call_tariff_table_data = "SELECT * FROM call_tariff order by rand() limit 100";
    std::cout<<"SELECT"<<std::endl;
	query_state=mysql_query(conn, mysql_call_tariff_table_data.c_str());
	if(query_state!=0)
	{
	   std::cout<<mysql_error(conn)<<std::endl<<std::endl;
	}
	res=mysql_store_result(conn);
	while((row=mysql_fetch_row(res))!=NULL)
	{
		row_number++;
		new Wt::WText(Wt::WString::fromUTF8(row[1]), call_tariff_table->elementAt(row_number, 0));
		new Wt::WText(Wt::WString::fromUTF8(row[2]), call_tariff_table->elementAt(row_number, 1));
		new Wt::WText(Wt::WString::fromUTF8(row[3]), call_tariff_table->elementAt(row_number, 2));
		new Wt::WText(Wt::WString::fromUTF8(row[4]), call_tariff_table->elementAt(row_number, 3));
		new Wt::WText(Wt::WString::fromUTF8(row[5]), call_tariff_table->elementAt(row_number, 4));
		new Wt::WText(Wt::WString::fromUTF8(row[6]), call_tariff_table->elementAt(row_number, 5));
		new Wt::WText(Wt::WString::fromUTF8(row[7]), call_tariff_table->elementAt(row_number, 6));
		new Wt::WText(Wt::WString::fromUTF8(row[8]), call_tariff_table->elementAt(row_number, 7));
		new Wt::WText(Wt::WString::fromUTF8(row[9]), call_tariff_table->elementAt(row_number, 8));
		new Wt::WText(Wt::WString::fromUTF8(row[10]), call_tariff_table->elementAt(row_number, 9));
		new Wt::WText(Wt::WString::fromUTF8(row[11]), call_tariff_table->elementAt(row_number, 10));
		new Wt::WText(Wt::WString::fromUTF8(row[12]), call_tariff_table->elementAt(row_number, 11));
		new Wt::WText(Wt::WString::fromUTF8(row[0]), call_tariff_table->elementAt(row_number, 12));
	}
	row_number = 0;
	call_tariff_table->addStyleClass("table form-inline table-bordered table-hover table-condensed table-striped top_mar top_pad");
	 std::cout<<"BUILD"<<std::endl;;

	mysql_free_result(res);
	mysql_close(conn);



    dialog->contents()->addStyleClass("form-group");



    //Wt::WPushButton *ok = new Wt::WPushButton("OK", dialog->footer());
    //ok->setDefault(true);


    Wt::WPushButton *cancel = new Wt::WPushButton(Wt::WString::fromUTF8("Выход"), dialog->footer());
    dialog->rejectWhenEscapePressed();


   //search
    Tarif_search_button->clicked().connect(std::bind([=] () {
 try {
	 std::cout<<"Trying to search tariff"<<std::endl;
    	call_tariff_table->clear();
    	int row_number2 = 0;
    	std::string mysql_search_call_tariff_table_data="";
    	std::string tarif_search_text=Tarif_search_edit->text().toUTF8();
    	mysql_init(&mysql);
    	conn=mysql_real_connect(&mysql, server, user, password, database, 0, 0, 0);
    	if(conn==NULL)
    	{
    		std::cout<<mysql_error(&mysql)<<std::endl<<std::endl;
    	}
    	mysql_query(&mysql,"SET NAMES 'UTF8'");




   if (tarif_search_text=="")
	   {
	   mysql_search_call_tariff_table_data = "SELECT * FROM call_tariff order by rand() limit 100";

	   } else {

	    mysql_search_call_tariff_table_data = "SELECT * FROM account_database.call_tariff WHERE locate('"+ tarif_search_text +"', zone_description) "
"OR  locate('"+ tarif_search_text +"', country) OR  locate('"+ tarif_search_text +"', description) OR  locate('"+ tarif_search_text +"', code) LIMIT 30";
	   }



   query_state=mysql_query(conn, mysql_search_call_tariff_table_data.c_str());
   std::cout<<"Trying to search tariff query"<<std::endl;

   if(query_state!=0)
   	   	{
   	   	   std::cout<<mysql_error(conn)<<std::endl<<std::endl;
   	   	}
   	   	res=mysql_store_result(conn);
   	   	while((row=mysql_fetch_row(res))!=NULL)
   	   	{
   	   		row_number2++;
   	   		new Wt::WText(Wt::WString::fromUTF8(row[1]), call_tariff_table->elementAt(row_number2, 0));
   	   		new Wt::WText(Wt::WString::fromUTF8(row[2]), call_tariff_table->elementAt(row_number2, 1));
   	   		new Wt::WText(Wt::WString::fromUTF8(row[3]), call_tariff_table->elementAt(row_number2, 2));
   	   		new Wt::WText(Wt::WString::fromUTF8(row[4]), call_tariff_table->elementAt(row_number2, 3));
   	   		new Wt::WText(Wt::WString::fromUTF8(row[5]), call_tariff_table->elementAt(row_number2, 4));
   	   		new Wt::WText(Wt::WString::fromUTF8(row[6]), call_tariff_table->elementAt(row_number2, 5));
   	   		new Wt::WText(Wt::WString::fromUTF8(row[7]), call_tariff_table->elementAt(row_number2, 6));
   	   		new Wt::WText(Wt::WString::fromUTF8(row[8]), call_tariff_table->elementAt(row_number2, 7));
   	   		new Wt::WText(Wt::WString::fromUTF8(row[9]), call_tariff_table->elementAt(row_number2, 8));
   	   		new Wt::WText(Wt::WString::fromUTF8(row[10]), call_tariff_table->elementAt(row_number2, 9));
   	   		new Wt::WText(Wt::WString::fromUTF8(row[11]), call_tariff_table->elementAt(row_number2, 10));
   	   		new Wt::WText(Wt::WString::fromUTF8(row[12]), call_tariff_table->elementAt(row_number2, 11));

   	   	}
   		mysql_free_result(res);
   		mysql_close(conn);
 }catch (const std::exception& e) {std::cout <<"Tariff search -> "<< e.what()<<std::endl;}
   	 std::cout<<"Trying to search tariff END"<<std::endl;

    }));



    // Accept the dialog
    save_exit_button->clicked().connect(std::bind([=] () {
	    dialog->accept();
    }));


    // Reject the dialog
    cancel->clicked().connect(dialog, &Wt::WDialog::reject);


    // Process the dialog result.
    dialog->finished().connect(std::bind([=] () {
	if (dialog->result() == Wt::WDialog::Accepted)
	{
	}

	delete dialog;
    }));

    dialog->show();
    std::cout<<"END"<<std::endl;
}

//abadon




extern void WtAccounts::subscriber_fullName_changed() {
	try {
	//treeTable->tree()->itemSelectionChanged()
    Wt::WMessageBox *messageBox;

    //Get sub name from left menu
	std::string changedSubscriberName = "";
	Wt::WTreeNode *selected_node; // operator* returns contents of an interator
	std::set<Wt::WTreeNode* > highlightedRows = ui->user_treeTable->tree()->selectedNodes();
	if (!highlightedRows.empty())
	{
		for (std::set<Wt::WTreeNode* >::iterator i = highlightedRows.begin(); i != highlightedRows.end(); ++i)
		{
		  selected_node = *i;
		}


		changedSubscriberName = selected_node->label()->text().toUTF8();

		highlightedRows.clear();
/////








		mysql_init(&mysql);
		conn=mysql_real_connect(&mysql, server, user, password, database, 0, 0, 0);
		if(conn==NULL)
		{
		    std::cout<<mysql_error(&mysql)<<std::endl<<std::endl;
		}
		mysql_query(&mysql,"SET NAMES 'UTF8'");


	// add node form mysql table
		std::string mysql_get_subscriber_info = "SELECT subscriber_id, full_name, account_number, tariff_plan, date_since, date_by FROM subscriber WHERE subscriber.full_name = '"+changedSubscriberName+"'";
		query_state=mysql_query(conn, mysql_get_subscriber_info.c_str());
		if(query_state!=0)
		{
		   std::cout<<mysql_error(conn)<<std::endl<<std::endl;
		}
		res=mysql_store_result(conn);
		std::cout<<"MySQL Values in the amaDB Table.15"<<std::endl<<std::endl;
		row=mysql_fetch_row(res);
		subscriber_id_view_mode = boost::lexical_cast<std::string>(row[0]);
		ui->user_info_groupbox->setTitle(Wt::WString::fromUTF8("Абонент ") + Wt::WString::fromUTF8(row[1]));
		ui->personal_account_edit->setText(Wt::WString::fromUTF8(row[2]));
		ui->user_name_edit->setText(Wt::WString::fromUTF8(row[1]));
		ui->tariff_edit->setText(Wt::WString::fromUTF8(row[3]));

		if (boost::lexical_cast<std::string>(row[4]) == "0000-00-00")
		{
			ui->include_date_edit->setText("");
		} else
		{
			ui->include_date_edit->setText(Wt::WString::fromUTF8(row[4]));
		}

		if (boost::lexical_cast<std::string>(row[5]) == "0000-00-00")
		{
			ui->disable_date_edit->setText("");
		} else
		{
			ui->disable_date_edit->setText(Wt::WString::fromUTF8(row[5]));
		}

		//mysql_free_result(res);



		std::string mysql_get_ip_address_and_phone_numbers = "SELECT ip_address, number FROM ip_addresses, phone_numbers "
				"WHERE ip_addresses.subscriber_id = '"+subscriber_id_view_mode+"' "
				"AND ip_addresses.subscriber_id = phone_numbers.subscriber_id";


		query_state=mysql_query(conn, mysql_get_ip_address_and_phone_numbers.c_str());

		std::string ip_and_numbers = "";
		if(query_state!=0)
		{
			std::cout<<mysql_error(conn)<<std::endl<<std::endl;
		}
		add_res=mysql_store_result(conn);
		row=mysql_fetch_row(add_res);
		if (row != NULL)
		{
			if (boost::lexical_cast<std::string>(row[0])!= "") ip_and_numbers.append(boost::lexical_cast<std::string>(row[0]));
			if (boost::lexical_cast<std::string>(row[0]) != "" && boost::lexical_cast<std::string>(row[1]) != "")
			{
				ip_and_numbers.append(", ");
				ip_and_numbers.append(boost::lexical_cast<std::string>(row[1]));
			}
		}
		ui->ip_number_edit->setText(Wt::WString::fromUTF8(ip_and_numbers));

		mysql_free_result(res);
		mysql_free_result(add_res);








		std::string current_month;
		std::string current_year;
		//check year
		std::string ResulYearCombo="";
		current_year=ui->year_combo_box->currentText().toUTF8();
		//check month
		int ResulMonthCombo_index;

		std::string check_date_temp="";
		ResulMonthCombo_index=ui->month_combo_box->currentIndex();
		if (ResulMonthCombo_index==0){
			check_date_temp=std::to_string(std::stoi(current_year)-1)+"-12-31";
		}else {
			check_date_temp=current_year+"-"+std::to_string(ResulMonthCombo_index)+"-31";
		}

         std::cout<<std::endl<<check_date_temp<<"<Last MOnth"<<std::endl;
		ResulMonthCombo_index++;
		current_month=std::to_string(ResulMonthCombo_index);

		//current year and month
//		std::string current_month = boost::lexical_cast<std::string>(boost::posix_time::second_clock::local_time().date().month().as_number());
//		std::string current_year = boost::lexical_cast<std::string>(boost::posix_time::second_clock::local_time().date().year());



		// total month credit table
		ui->total_month_credit_table->clear();
		ui->total_month_credit_table->refresh();

		ui->total_month_credit_table->setHeaderCount(1);

		ui->total_month_credit_table->elementAt(0, 0)->addWidget(new Wt::WText(Wt::WString::fromUTF8("Услуга")));
		ui->total_month_credit_table->elementAt(0, 1)->addWidget(new Wt::WText(Wt::WString::fromUTF8("Код")));
		ui->total_month_credit_table->elementAt(0, 2)->addWidget(new Wt::WText(Wt::WString::fromUTF8("Количество")));
		ui->total_month_credit_table->elementAt(0, 3)->addWidget(new Wt::WText(Wt::WString::fromUTF8("Сумма")));
		ui->total_month_credit_table->elementAt(0, 4)->addWidget(new Wt::WText(Wt::WString::fromUTF8("Номер/IP")));
		ui->total_month_credit_table->elementAt(0, 5)->addWidget(new Wt::WText(Wt::WString::fromUTF8("Использование")));
		ui->total_month_credit_table->elementAt(0, 6)->addWidget(new Wt::WText(Wt::WString::fromUTF8("Описание")));


/*
	    new Wt::WText(Wt::WString::fromUTF8("Абонентская плата за телефон"), ui->total_month_credit_table->elementAt(1, 0));
	    new Wt::WText(Wt::WString::fromUTF8("1.1"), ui->total_month_credit_table->elementAt(1, 1));
	    new Wt::WText(Wt::WString::fromUTF8("1"), ui->total_month_credit_table->elementAt(1, 2));
	    new Wt::WText(Wt::WString::fromUTF8("619.3500"), ui->total_month_credit_table->elementAt(1, 3));
	    new Wt::WText(Wt::WString::fromUTF8(""), ui->total_month_credit_table->elementAt(1, 4));
	    new Wt::WText(Wt::WString::fromUTF8("0"), ui->total_month_credit_table->elementAt(1, 5));
	    new Wt::WText(Wt::WString::fromUTF8(""), ui->total_month_credit_table->elementAt(1, 6));
*/

		int row_number = 0;

		std::string mysql_total_credit_table_data = "SELECT subscriber_transaction.description, quantity, code "
													"FROM subscriber_transaction, subscriber_services "
													"WHERE subscriber_transaction.subscriber_id = '"+subscriber_id_view_mode+"' "
													"AND subscriber_transaction.description = subscriber_services.service_name "
													"AND subscriber_transaction.transaction_type = 'Начисление' "
													"AND MONTH(transaction_date) = '"+current_month+"' "
													"AND YEAR(transaction_date) = '"+current_year+"'";

		query_state=mysql_query(conn, mysql_total_credit_table_data.c_str());
		if(query_state!=0)
		{
		   std::cout<<mysql_error(conn)<<std::endl<<std::endl;
		}
		res=mysql_store_result(conn);

		while((row=mysql_fetch_row(res))!=NULL)
		{
            //std::cout<<
			row_number++;
			new Wt::WText(Wt::WString::fromUTF8(row[0]), ui->total_month_credit_table->elementAt(row_number, 0));
			new Wt::WText(Wt::WString::fromUTF8(row[2]), ui->total_month_credit_table->elementAt(row_number, 1));
			new Wt::WText(Wt::WString::fromUTF8("1"), ui->total_month_credit_table->elementAt(row_number, 2));
			new Wt::WText(Wt::WString::fromUTF8(row[1]), ui->total_month_credit_table->elementAt(row_number, 3));
			new Wt::WText(Wt::WString::fromUTF8(""), ui->total_month_credit_table->elementAt(row_number, 4));
			new Wt::WText(Wt::WString::fromUTF8("0"), ui->total_month_credit_table->elementAt(row_number, 5));
			new Wt::WText(Wt::WString::fromUTF8(""), ui->total_month_credit_table->elementAt(row_number, 6));
		}

		ui->total_month_credit_table->addStyleClass("table form-inline table-bordered table-hover table-condensed table-striped");

		mysql_free_result(res);



		// month credit table
		ui->month_credit_table->clear();
		ui->month_credit_table->refresh();
		ui->month_credit_table->setHeaderCount(1);

		ui->month_credit_table->elementAt(0, 0)->addWidget(new Wt::WText(Wt::WString::fromUTF8("Дата")));
		ui->month_credit_table->elementAt(0, 1)->addWidget(new Wt::WText(Wt::WString::fromUTF8("Начисления")));
		ui->month_credit_table->elementAt(0, 2)->addWidget(new Wt::WText(Wt::WString::fromUTF8("Оплачено")));
		ui->month_credit_table->elementAt(0, 3)->addWidget(new Wt::WText(Wt::WString::fromUTF8("Описание")));
		ui->month_credit_table->elementAt(0, 4)->addWidget(new Wt::WText(Wt::WString::fromUTF8("Код")));
		ui->month_credit_table->elementAt(0, 5)->addWidget(new Wt::WText(Wt::WString::fromUTF8("Период")));
		ui->month_credit_table->elementAt(0, 6)->addWidget(new Wt::WText(Wt::WString::fromUTF8("Номер/IP")));
		ui->month_credit_table->elementAt(0, 7)->addWidget(new Wt::WText(Wt::WString::fromUTF8("ID")));

		std::string mysql_month_credit_table_data = "SELECT transaction_id, transaction_type, transaction_date, "
													"subscriber_transaction.description, quantity, code, charging_period "
													"FROM subscriber_transaction, subscriber_services "
													"WHERE subscriber_transaction.subscriber_id = '"+subscriber_id_view_mode+"' "
													"AND subscriber_transaction.description = subscriber_services.service_name "
													"AND MONTH(transaction_date) = '"+current_month+"' "
													"AND YEAR(transaction_date) = '"+current_year+"'";

		row_number = 0;

		query_state=mysql_query(conn, mysql_month_credit_table_data.c_str());
		if(query_state!=0)
		{
		   std::cout<<mysql_error(conn)<<std::endl<<std::endl;
		}
		res=mysql_store_result(conn);

		std::string transaction_type = "";

		while((row=mysql_fetch_row(res))!=NULL)
		{
			transaction_type = boost::lexical_cast<std::string>(row[1]);
			row_number++;
			new Wt::WText(Wt::WString::fromUTF8(row[2]), ui->month_credit_table->elementAt(row_number, 0));
			if (transaction_type == "Начисление")
			{
				new Wt::WText(Wt::WString::fromUTF8(row[4]), ui->month_credit_table->elementAt(row_number, 1));
				new Wt::WText(Wt::WString::fromUTF8("0.0000"), ui->month_credit_table->elementAt(row_number, 2));
			} else
			{
				new Wt::WText(Wt::WString::fromUTF8("0.0000"), ui->month_credit_table->elementAt(row_number, 1));
				new Wt::WText(Wt::WString::fromUTF8(row[4]), ui->month_credit_table->elementAt(row_number, 2));
			}
			new Wt::WText(Wt::WString::fromUTF8(row[3]), ui->month_credit_table->elementAt(row_number, 3));
			new Wt::WText(Wt::WString::fromUTF8(row[5]), ui->month_credit_table->elementAt(row_number, 4));
			new Wt::WText(Wt::WString::fromUTF8(row[6]), ui->month_credit_table->elementAt(row_number, 5));
			new Wt::WText(Wt::WString::fromUTF8(""), ui->month_credit_table->elementAt(row_number, 6));
			new Wt::WText(Wt::WString::fromUTF8(row[0]), ui->month_credit_table->elementAt(row_number, 7));
		}

/*

	    new Wt::WText(Wt::WString::fromUTF8("03.03.2016"), ui->month_credit_table->elementAt(1, 0));
	    new Wt::WText(Wt::WString::fromUTF8("1500.0000"), ui->month_credit_table->elementAt(1, 1));
	    new Wt::WText(Wt::WString::fromUTF8("0.0000"), ui->month_credit_table->elementAt(1, 2));
	    new Wt::WText(Wt::WString::fromUTF8("619.3500"), ui->month_credit_table->elementAt(1, 3));
	    new Wt::WText(Wt::WString::fromUTF8("Абонентская плата за телефон"), ui->month_credit_table->elementAt(1, 4));
	    new Wt::WText(Wt::WString::fromUTF8("1.1"), ui->month_credit_table->elementAt(1, 5));
	    new Wt::WText(Wt::WString::fromUTF8("Каждый месяц"), ui->month_credit_table->elementAt(1, 6));

*/

		ui->month_credit_table->addStyleClass("table form-inline table-bordered table-hover table-condensed table-striped");



		// traffic and calls table
		std::map<std::string,std::string> MapCallType
		{{"mobile call","Мобильный"},
		{"intercity call","Межгудогородний"},
		{"international call","Международный"},
		{"hot line","Горячия линия"},
		{"fixed service","Фиксированные сервесы"},
		{"inner","Городской"},
		{"incoming","Входяший"}};



		ui->traffic_call_table->clear();
		ui->traffic_call_table->refresh();

		ui->traffic_call_table->setHeaderCount(1);

		ui->traffic_call_table->elementAt(0, 0)->addWidget(new Wt::WText(Wt::WString::fromUTF8("Тип вызова")));
		ui->traffic_call_table->elementAt(0, 1)->addWidget(new Wt::WText(Wt::WString::fromUTF8("Категория")));
		ui->traffic_call_table->elementAt(0, 2)->addWidget(new Wt::WText(Wt::WString::fromUTF8("Количество")));
		ui->traffic_call_table->elementAt(0, 3)->addWidget(new Wt::WText(Wt::WString::fromUTF8("Стоимость")));
		ui->traffic_call_table->elementAt(0, 4)->addWidget(new Wt::WText(Wt::WString::fromUTF8("Номер/IP")));
		ui->traffic_call_table->elementAt(0, 5)->addWidget(new Wt::WText(Wt::WString::fromUTF8("Объем")));



//		std::string mysql_traffic_and_calls_table_data = "SELECT call_type,Count(*),SUM(call_cost),N.number,Sum(milli_second)"
//				" FROM account_database.ama_data  "
//				"INNER JOIN(SELECT c.number FROM account_database.ama_data AS a "
//				"INNER JOIN account_database.phone_numbers AS c "
//				"ON c.subscriber_id = '"+subscriber_id_view_mode+"'"
//				"AND MONTH(a.start_date)='"+current_month+"' AND YEAR(a.start_date)='"+current_year+"' AND (c.number=a.numberA OR c.number=a.numberB) "
//				"GROUP BY  c.number) N ON N.number = ama_data.numberA OR N.number = ama_data.numberB Group by N.number,call_type;";

		std::string mysql_traffic_and_calls_table_data = "SELECT ip_address FROM account_database.ip_addresses WHERE subscriber_id='"+subscriber_id_view_mode+"'";

		row_number = 0;

		query_state=mysql_query(conn, mysql_traffic_and_calls_table_data.c_str());
		if(query_state!=0)
		{
			std::cout<<mysql_error(conn)<<std::endl<<std::endl;
		}
		res=mysql_store_result(conn);
		//if subscriber have IP
		if ((row=mysql_fetch_row(res))!=NULL){
			std::string Cur_user_IP=row[0];
			mysql_traffic_and_calls_table_data = "SELECT sum(total_bytes),count(total_bytes) FROM account_database.cal_netflow_data "
					"WHERE source_address='"+Cur_user_IP+"' AND MONTH(receive_date) = '"+current_month+"' AND YEAR(receive_date)='"+current_year+"'";

			row_number = 0;

			query_state=mysql_query(conn, mysql_traffic_and_calls_table_data.c_str());
			if(query_state!=0)
			{
				std::cout<<mysql_error(conn)<<std::endl<<std::endl;
			}
			res=mysql_store_result(conn);
			if ((row=mysql_fetch_row(res))!=NULL){
				if(row[0]!=NULL){//check again b/c of sum(total_bytes)
					row_number++;
					new Wt::WText(Wt::WString::fromUTF8("Учет Трафика"), ui->traffic_call_table->elementAt(row_number, 0));
					new Wt::WText(Wt::WString::fromUTF8("-"), ui->traffic_call_table->elementAt(row_number, 1));
					new Wt::WText(Wt::WString::fromUTF8(row[1]), ui->traffic_call_table->elementAt(row_number, 2));
					new Wt::WText(Wt::WString::fromUTF8("0"), ui->traffic_call_table->elementAt(row_number, 3));
					new Wt::WText(Wt::WString::fromUTF8(Cur_user_IP), ui->traffic_call_table->elementAt(row_number, 4));
					long long int row4=std::atoll(row[0])/125000;
					new Wt::WText(Wt::WString::fromUTF8(std::to_string(row4)+" MB"), ui->traffic_call_table->elementAt(row_number, 5));

				}}}


		mysql_traffic_and_calls_table_data = "SELECT  call_type,COUNT(*),SUM(call_cost), N.number,SUM(milli_second)"
				" FROM account_database.ama_data INNER JOIN "
				"(SELECT number FROM  account_database.phone_numbers  WHERE subscriber_id ='"+subscriber_id_view_mode+"')N "
				" ON N.number = ama_data.numberA OR N.number = ama_data.numberB  "
				"WHERE MONTH(start_date) = '"+current_month+"' AND YEAR(start_date)='"+current_year+"' GROUP BY N.number,call_type;";






		query_state=mysql_query(conn, mysql_traffic_and_calls_table_data.c_str());
		if(query_state!=0)
		{
			std::cout<<mysql_error(conn)<<std::endl<<std::endl;
		}
		res=mysql_store_result(conn);


		while((row=mysql_fetch_row(res))!=NULL)
		{
			row_number++;
			new Wt::WText(Wt::WString::fromUTF8(MapCallType[std::string(row[0])]), ui->traffic_call_table->elementAt(row_number, 0));
			new Wt::WText(Wt::WString::fromUTF8("-"), ui->traffic_call_table->elementAt(row_number, 1));
			new Wt::WText(Wt::WString::fromUTF8(row[1]), ui->traffic_call_table->elementAt(row_number, 2));
			new Wt::WText(Wt::WString::fromUTF8(row[2]), ui->traffic_call_table->elementAt(row_number, 3));
			new Wt::WText(Wt::WString::fromUTF8(row[3]), ui->traffic_call_table->elementAt(row_number, 4));
		    int row4=std::atoi(row[4])/1000;
			new Wt::WText(Wt::WString::fromUTF8(std::to_string(row4)+" сек"), ui->traffic_call_table->elementAt(row_number, 5));
		}

		std::cout<<"subscriber_id_view_mode  "<<subscriber_id_view_mode<<std::endl;


		ui->traffic_call_table->addStyleClass("table form-inline table-bordered table-hover table-condensed table-striped");
		double Sub_main_dept;
		double Sub_main_paid;
		double Sub_last_dept;
		std::string Sub_main_diffrance;

				mysql_get_ip_address_and_phone_numbers = "SELECT sum(quantity)"
						"FROM subscriber_transaction "
						"WHERE subscriber_transaction.transaction_type = 'Начисление' "
						"AND MONTH(transaction_date) = '"+current_month+"' "
						"AND YEAR(transaction_date) = '"+current_year+"' "
				 "AND subscriber_id='"+subscriber_id_view_mode+"'";
				query_state=mysql_query(conn, mysql_get_ip_address_and_phone_numbers.c_str());


				if(query_state!=0)
				{
					std::cout<<mysql_error(conn)<<std::endl<<std::endl;
				}
				add_res=mysql_store_result(conn);
				row=mysql_fetch_row(add_res);
				if (row != NULL)
				{
					if (row[0]!=NULL){Sub_main_dept=boost::lexical_cast<double>(row[0]);
					ui->month_credit_edit->setText(Wt::WString::fromUTF8(row[0]));
					std::cout<<"Sub_main_dept  "<<Sub_main_dept<<std::endl;} else
					 ui->month_credit_edit->setText(Wt::WString::fromUTF8("0"));
					mysql_free_result(add_res);
				}

				mysql_get_ip_address_and_phone_numbers = "SELECT sum(quantity)"
						"FROM subscriber_transaction "
						"WHERE subscriber_transaction.transaction_type = 'Оплата' "
						"AND MONTH(transaction_date) = '"+current_month+"' "
						"AND YEAR(transaction_date) = '"+current_year+"' "
				 "AND subscriber_id='"+subscriber_id_view_mode+"'";
				query_state=mysql_query(conn, mysql_get_ip_address_and_phone_numbers.c_str());


				if(query_state!=0)
				{
					std::cout<<mysql_error(conn)<<std::endl<<std::endl;
				}
				add_res=mysql_store_result(conn);
				row=mysql_fetch_row(add_res);
				if (row != NULL)
				{
					if (row[0]!=NULL){Sub_main_paid=boost::lexical_cast<double>(row[0]);
					ui->month_paid_edit->setText(Wt::WString::fromUTF8(row[0]));}
					else ui->month_paid_edit->setText(Wt::WString::fromUTF8("0"));
					mysql_free_result(add_res);
				}



              try {
				mysql_get_ip_address_and_phone_numbers = "SELECT sum(quantity) FROM account_database.subscriber_transaction where subscriber_id ='"+subscriber_id_view_mode+"'  and  transaction_date between '2014-02-03' and str_to_date('"+check_date_temp+"', '%Y-%m-%d') and transaction_type = 'Начисление'";

				query_state=mysql_query(conn, mysql_get_ip_address_and_phone_numbers.c_str());

				if(query_state!=0)
				{
					std::cout<<mysql_error(conn)<<std::endl<<std::endl;
				}
				add_res=mysql_store_result(conn);
				row=mysql_fetch_row(add_res);
				if (row != NULL)
				{
					if (row[0]!=NULL){Sub_last_dept=boost::lexical_cast<double>(row[0]);
					ui->initial_debt_edit->setText(std::to_string(Sub_last_dept));
					}else ui->initial_debt_edit->setText(Wt::WString::fromUTF8("0"));
					mysql_free_result(add_res);
				}

				mysql_get_ip_address_and_phone_numbers = "SELECT sum(quantity) FROM account_database.subscriber_transaction where subscriber_id ='"+subscriber_id_view_mode+"'  and  transaction_date between '2014-02-03' and str_to_date('"+check_date_temp+"', '%Y-%m-%d') and transaction_type = 'Оплата'";

				query_state=mysql_query(conn, mysql_get_ip_address_and_phone_numbers.c_str());

				if(query_state!=0)
				{
					std::cout<<mysql_error(conn)<<std::endl<<std::endl;
				}
				add_res=mysql_store_result(conn);
				row=mysql_fetch_row(add_res);
				if (row != NULL)
				{
					if (row[0]!=NULL){Sub_last_dept=Sub_last_dept-boost::lexical_cast<double>(row[0]);
					ui->initial_debt_edit->setText(std::to_string(Sub_last_dept));}
					mysql_free_result(add_res);
				}



                double Sub_main_diffrance_number = Sub_main_dept+Sub_last_dept-Sub_main_paid;
				Sub_main_diffrance = std::to_string(Sub_main_diffrance_number);
				ui->debt_edit->setText(Sub_main_diffrance);
              } catch (const std::exception& e) {std::cout <<"Get Dept calculation -> "<< e.what()<<std::endl;}




		mysql_free_result(res);
		mysql_close(conn);


		/*
		messageBox = new Wt::WMessageBox(Wt::WString::fromUTF8("Adilbek cool: "), Wt::WString::fromUTF8(changedSubscriberName), Wt::Information, Wt::Yes | Wt::No);
	    messageBox->buttonClicked().connect(std::bind([=] () {
		delete messageBox;
	    }));

	    messageBox->show();
		*/

	}
	//+ Wt::WString::fromUTF8(changedSubscriberName)



	} catch (const std::exception& e) {std::cout <<"Refresh -> "<< e.what()<<std::endl;}
}



// herdre functions
// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^


// search subscribers by name, IP address, or phone number
extern void WtAccounts::search_subscribers(std::string operation_name) {

	std::string ResultOf_Search = "";
	ResultOf_Search = ui->user_search_edit->text().toUTF8();

	if (ResultOf_Search == "")
	{   try {
		std::cout << "Empty Search Start"<<std::endl;
		//subscriber_show_operation_tab("view");

		mysql_init(&mysql);
		conn=mysql_real_connect(&mysql, server, user, password, database, 0, 0, 0);
		if(conn==NULL)
		{
		    std::cout<<mysql_error(&mysql)<<std::endl<<std::endl;
		}
		mysql_query(&mysql,"SET NAMES 'UTF8'");

	    ui->user_tree_root = new Wt::WTreeTableNode(Wt::WString::fromUTF8("ТОО"));
		ui->user_treeTable->setTreeRoot(ui->user_tree_root, Wt::WString::fromUTF8("Группа"));

	    Wt::WTreeTableNode *tree_node;

	// add node form mysql table
		query_state=mysql_query(conn, "select * from subscriber_group ORDER BY group_name");
		if(query_state!=0)
		{
		   std::cout<<mysql_error(conn)<<std::endl<<std::endl;
		}
		res=mysql_store_result(conn);
		std::string mysql_get_subscriber_fullName = "";
		std::cout<<"MySQL Values in the amaDB Table.16"<<std::endl<<std::endl;
		while((row=mysql_fetch_row(res))!=NULL)
		{
			ui->user_tree_group  = new Wt::WTreeTableNode(Wt::WString::fromUTF8(row[1]), 0, ui->user_tree_root);
			ui->user_tree_group->setSelectable(false);

			mysql_get_subscriber_fullName = "select full_name from subscriber where subscriber.group_id = '"+boost::lexical_cast<std::string>(row[0])+"' ORDER BY full_name";
			query_state=mysql_query(conn, mysql_get_subscriber_fullName.c_str());
			if(query_state!=0)
			{
			   std::cout<<mysql_error(conn)<<std::endl<<std::endl;
			}
			add_res=mysql_store_result(conn);
			while((add_row=mysql_fetch_row(add_res))!=NULL)
			{
				//ui->user_tree_group ->setColumnWidget(1, new Wt::WText(Wt::WString::fromUTF8(add_row[0])));
				tree_node = new Wt::WTreeTableNode(Wt::WString::fromUTF8(add_row[0]), 0, ui->user_tree_group);
			}
		}

		mysql_free_result(res);
		mysql_free_result(add_res);
		mysql_close(conn);

		ui->user_tree_root->expand();
		std::cout << "Empty Search End"<<std::endl;
	} catch (const std::exception& e) {std::cout <<"Search 1 -> "<< e.what()<<std::endl;}
	}
	else
	{  try {
		std::cout << "Search Start"<<std::endl;
		mysql_init(&mysql);
		conn=mysql_real_connect(&mysql, server, user, password, database, 0, 0, 0);
		if(conn==NULL)
		{
		 std::cout<<mysql_error(&mysql)<<std::endl<<std::endl;
		}
		mysql_query(&mysql,"SET NAMES 'UTF8'");


		ui->user_treeTable->setStyleClass(Wt::WString::fromUTF8("Wt-treetable col-lg-12 col-md-12"));
		ui->user_treeTable->tree()->setSelectionMode(Wt::SingleSelection);
		//ui->user_treeTable->addColumn(Wt::WString::fromUTF8("Абонентов"), 100);

		ui->user_tree_root = new Wt::WTreeTableNode(Wt::WString::fromUTF8("Результаты поиска"));
		ui->user_tree_root->setSelectable(false);
		ui->user_treeTable->setTreeRoot(ui->user_tree_root, Wt::WString::fromUTF8("Поиск"));


		Wt::WTreeTableNode *tree_node;

		std::string mysql_get_subscriber_fullName = " SELECT full_name FROM account_database.subscriber WHERE locate('"+ResultOf_Search+"',full_name)>0 UNION ALL "
		"SELECT full_name FROM account_database.subscriber AS a INNER JOIN account_database.phone_numbers AS p ON a.subscriber_id=p.subscriber_id WHERE locate('"+ResultOf_Search+"', p.number)>0 UNION ALL "
		" SELECT full_name FROM account_database.subscriber AS a INNER JOIN account_database.ip_addresses AS i ON a.subscriber_id=i.subscriber_id WHERE locate('"+ResultOf_Search+"', i.ip_address)>0 ORDER BY full_name";
		//std::cout<<"Trying to Search "<<ResultOf_Search<<std::endl<<std::endl;

		query_state=mysql_query(conn, mysql_get_subscriber_fullName.c_str());

		if(query_state!=0)
		{
		 std::cout<<mysql_error(conn)<<std::endl<<std::endl;
		}
		add_res=mysql_store_result(conn);

		add_row=mysql_fetch_row(add_res);
		if (add_row==NULL){

			ui->user_tree_root = new Wt::WTreeTableNode(Wt::WString::fromUTF8("Нет совпадений в базе"));
			ui->user_tree_root->setSelectable(false);
			ui->user_treeTable->setTreeRoot(ui->user_tree_root, Wt::WString::fromUTF8("Поиск"));
		}



		while (add_row!=NULL)
		{
			tree_node = new Wt::WTreeTableNode(Wt::WString::fromUTF8(add_row[0]), 0, ui->user_tree_root);
			add_row=mysql_fetch_row(add_res);
		}

		mysql_free_result(add_res);
		mysql_close(conn);

		ui->user_tree_root->expand();
		std::cout << "Search End"<<std::endl;
	} catch (const std::exception& e) {std::cout <<"create_phone_number_dialog -> "<< e.what()<<std::endl;}
	}
}

//End of Search



extern void WtAccounts::p_account_operation_Data(std::string operation_name)
{
//get name of M that pressed
std::string ResultOfoperationmeny="";
ResultOfoperationmeny=ui->p_account_operation_split_button_popup->result()->text().toUTF8();

//First check(if just table data) creat table 1st then perfom another function

	Wt::WMessageBox *messageBox;

	//check year
	std::string ResulYearCombo="";
	ResulYearCombo=ui->year_combo_box->currentText().toUTF8();
	//check month
	int ResulMonthCombo_index;
	ResulMonthCombo_index=ui->month_combo_box->currentIndex();ResulMonthCombo_index++;
	std::string ResulMonthCombo_index_string=std::to_string(ResulMonthCombo_index);



	std::string changedSubscriberName = "";
	Wt::WTreeNode *selected_node; // operator* returns contents of an interator
	std::set<Wt::WTreeNode* > highlightedRows = ui->user_treeTable->tree()->selectedNodes();


	//chek if any user selected
	if (!highlightedRows.empty())
					{

			Wt::WContainerWidget * CHECK_pop_tab_Temp = new Wt::WContainerWidget(ui->container_cp);
			Wt::WMenuItem * CHECK_pop_tab_mi_temp = ui->main_tabs->addTab(CHECK_pop_tab_Temp, Wt::WString::fromUTF8(""));;
			Wt::WTable *CHECK_user_treeTablef;
			CHECK_pop_tab_mi_temp->setCloseable(true);
			CHECK_pop_tab_mi_temp->enable();

			Wt::WContainerWidget *service_table_container = new Wt::WContainerWidget(CHECK_pop_tab_Temp);
			service_table_container->setHtmlTagName("div");
			service_table_container->setHeight(Wt::WLength("800px"));

			service_table_container->setOverflow(Wt::WContainerWidget::Overflow::OverflowAuto, Wt::Orientation::Vertical);

			CHECK_user_treeTablef = new Wt::WTable(service_table_container);
			CHECK_user_treeTablef->setId("CHECK_user_treeTable");
			CHECK_user_treeTablef->setStyleClass(Wt::WString::fromUTF8("table table-bordered table-striped table-hover table-condensed"));
			CHECK_user_treeTablef->setInline(0);
			CHECK_user_treeTablef->setHeaderCount(1, Wt::Orientation::Horizontal);
			CHECK_user_treeTablef->setHeaderCount(1, Wt::Orientation::Vertical);


			for (std::set<Wt::WTreeNode* >::iterator i = highlightedRows.begin(); i != highlightedRows.end(); ++i)
							     					{
							     					  selected_node = *i;
							     					}
				                      changedSubscriberName = selected_node->label()->text().toUTF8();


		  //for addition name in tab
		std::string Obriv=" ";
		 std::size_t pos_for_Obriv;
		 /*
		for(std::string::iterator it = changedSubscriberName.begin(); it != changedSubscriberName.end(); ++it) {


		}*/

		//for addition name in tab
		pos_for_Obriv = changedSubscriberName.find(' ');
		Obriv += changedSubscriberName.substr(0,pos_for_Obriv);
		/*for (auto single_char:changedSubscriberName){
			if (single_char!=' ') Obriv+=single_char;
			else break;
		 }*/

		CHECK_pop_tab_mi_temp->setText(Wt::WString::fromUTF8(ResultOfoperationmeny+Obriv));

					ui->main_tabs->setCurrentIndex(ui->main_tabs->indexOf(CHECK_pop_tab_Temp));

					CHECK_user_treeTablef->clear();
					CHECK_user_treeTablef->refresh();


					CHECK_user_treeTablef->setHeaderCount(1);


					//PDF
				Wt::WResource *pdf = new ReportResource(service_table_container,0);
				//service_table_container

				Wt::WPushButton *button2 = new Wt::WPushButton(Wt::WString::fromUTF8("Создать Отчет"),CHECK_pop_tab_Temp);
//CHECK_pop_tab_Temp
				button2->setLink(pdf);
					//PDF



					if (Wt::WString::fromUTF8("Телефонный трафик")==Wt::WString::fromUTF8(ResultOfoperationmeny)){

						CHECK_user_treeTablef->elementAt(0, 0)->addWidget(new Wt::WText(Wt::WString::fromUTF8("Устройство")));
						//CHECK_user_treeTablef->elementAt(0, 1)->addWidget(new Wt::WText(Wt::WString::fromUTF8("Запись")));1
						CHECK_user_treeTablef->elementAt(0, 2)->addWidget(new Wt::WText(Wt::WString::fromUTF8("Тип")));
						CHECK_user_treeTablef->elementAt(0, 3)->addWidget(new Wt::WText(Wt::WString::fromUTF8("Номер А")));
						CHECK_user_treeTablef->elementAt(0, 4)->addWidget(new Wt::WText(Wt::WString::fromUTF8("Номер Б")));
						CHECK_user_treeTablef->elementAt(0, 5)->addWidget(new Wt::WText(Wt::WString::fromUTF8("Дата")));
					    CHECK_user_treeTablef->elementAt(0, 6)->addWidget(new Wt::WText(Wt::WString::fromUTF8("Время")));
						//CHECK_user_treeTablef->elementAt(0, 7)->addWidget(new Wt::WText(Wt::WString::fromUTF8("Код")));
					    CHECK_user_treeTablef->elementAt(0, 8)->addWidget(new Wt::WText(Wt::WString::fromUTF8("Абонент")));
						//CHECK_user_treeTablef->elementAt(0, 9)->addWidget(new Wt::WText(Wt::WString::fromUTF8("Куда")));
						CHECK_user_treeTablef->elementAt(0, 10)->addWidget(new Wt::WText(Wt::WString::fromUTF8("Город")));
			     		CHECK_user_treeTablef->elementAt(0, 11)->addWidget(new Wt::WText(Wt::WString::fromUTF8("Категория")));
						CHECK_user_treeTablef->elementAt(0, 12)->addWidget(new Wt::WText(Wt::WString::fromUTF8("Секунд вызова")));
			     		CHECK_user_treeTablef->elementAt(0, 13)->addWidget(new Wt::WText(Wt::WString::fromUTF8("Стоимость")));


			       highlightedRows.clear();


mysql_init(&mysql);
conn=mysql_real_connect(&mysql, server, user, password, database, 0, 0, 0);
mysql_query(&mysql,"SET NAMES 'UTF8'");

			     	if(conn==NULL){
			     		std::cout<<mysql_error(&mysql)<<std::endl<<std::endl;}


			std::string mysql_subscriber_all_table_data = "SELECT c.* FROM account_database.phone_numbers "
	     			" AS a INNER JOIN account_database.ama_data AS "
	     			"c ON a.subscriber_id='"+subscriber_id_view_mode+"' "
	     					"AND (a.number=c.numberB OR a.number=c.numberA) "
	     					"AND year(c.start_date)=year(str_to_date('"+ResulYearCombo+"','%Y')) AND month(c.start_date)=month(str_to_date('"+ResulMonthCombo_index_string+"','%m'))";

			     				int row_number = 0;
			     				query_state=mysql_query(conn, mysql_subscriber_all_table_data.c_str());
			     				if(query_state!=0)
			     				{
			     				   std::cout<<mysql_error(conn)<<std::endl<<std::endl;
			     				}
			     				std::string TypeOfcall="";
			     				res=mysql_store_result(conn);
			     				while((row=mysql_fetch_row(res))!=NULL)
			     				{row_number++;





			     				if (Wt::WString::fromUTF8(row[11])=="mobile call") TypeOfcall="Мобильная связь";
			     				if (Wt::WString::fromUTF8(row[11])=="fixed service") TypeOfcall="Фиксированный сервис";
			     				if (Wt::WString::fromUTF8(row[11])=="intercity call") TypeOfcall="Междугородный";
			     				if (Wt::WString::fromUTF8(row[11])=="inner") TypeOfcall="Городской";
			     				if (Wt::WString::fromUTF8(row[11])=="hot line") TypeOfcall="Горячая линия";
			     				if (Wt::WString::fromUTF8(row[11])=="Unknown") TypeOfcall="Не Определен";
			     				if (Wt::WString::fromUTF8(row[11])=="incoming") TypeOfcall="Входяший";
			     				std::cout<<std::endl<<std::endl<<Wt::WString::fromUTF8(row[10])<<std::endl<<std::endl;

			     				new Wt::WText(Wt::WString::fromUTF8("Учет телефонных звонков"), CHECK_user_treeTablef->elementAt(row_number, 0));
			     				//new Wt::WText(Wt::WString::fromUTF8("Обычный"), CHECK_user_treeTablef->elementAt(row_number, 1));1
			     				new Wt::WText(Wt::WString::fromUTF8(row[1]), CHECK_user_treeTablef->elementAt(row_number, 3));
			     				new Wt::WText(Wt::WString::fromUTF8(row[2]), CHECK_user_treeTablef->elementAt(row_number, 4));
			     				new Wt::WText(Wt::WString::fromUTF8(row[3]), CHECK_user_treeTablef->elementAt(row_number, 5));
			     				new Wt::WText(Wt::WString::fromUTF8(row[4]), CHECK_user_treeTablef->elementAt(row_number, 6));
			     				new Wt::WText(Wt::WString::fromUTF8(changedSubscriberName), CHECK_user_treeTablef->elementAt(row_number, 8));

			     				new Wt::WText(Wt::WString::fromUTF8(row[13]), CHECK_user_treeTablef->elementAt(row_number, 10));
			     				new Wt::WText(Wt::WString::fromUTF8(TypeOfcall), CHECK_user_treeTablef->elementAt(row_number, 2));
                                double durtaion_call = boost::lexical_cast<double>(row[7])/1000;

                                durtaion_call = (int)(durtaion_call / 0.01) * 0.01;


                                std::string durtaion_call_string=std::to_string(durtaion_call);
                                new Wt::WText(Wt::WString::fromUTF8(durtaion_call_string), CHECK_user_treeTablef->elementAt(row_number, 12));
			     				new Wt::WText(Wt::WString::fromUTF8(row[10]), CHECK_user_treeTablef->elementAt(row_number, 13));
			     				TypeOfcall="";
			     				}
			     				CHECK_user_treeTablef->refresh();
			     				mysql_free_result(res);
			     				mysql_close(conn);
					}


					if (Wt::WString::fromUTF8("Netflow трафик")==Wt::WString::fromUTF8(ResultOfoperationmeny)){


						CHECK_user_treeTablef->elementAt(0, 0)->addWidget(new Wt::WText(Wt::WString::fromUTF8("Устройство")));
						CHECK_user_treeTablef->elementAt(0, 1)->addWidget(new Wt::WText(Wt::WString::fromUTF8("Источник IP")));
						CHECK_user_treeTablef->elementAt(0, 2)->addWidget(new Wt::WText(Wt::WString::fromUTF8("Порт Источника")));
						CHECK_user_treeTablef->elementAt(0, 3)->addWidget(new Wt::WText(Wt::WString::fromUTF8("Цель IP")));
						CHECK_user_treeTablef->elementAt(0, 4)->addWidget(new Wt::WText(Wt::WString::fromUTF8("Порт назначения")));
						CHECK_user_treeTablef->elementAt(0, 5)->addWidget(new Wt::WText(Wt::WString::fromUTF8("Протокол")));
						CHECK_user_treeTablef->elementAt(0, 6)->addWidget(new Wt::WText(Wt::WString::fromUTF8("Дата/Время")));
						CHECK_user_treeTablef->elementAt(0, 7)->addWidget(new Wt::WText(Wt::WString::fromUTF8("Байт передано")));
						CHECK_user_treeTablef->elementAt(0, 8)->addWidget(new Wt::WText(Wt::WString::fromUTF8("Абонент")));




			       highlightedRows.clear();


mysql_init(&mysql);
conn=mysql_real_connect(&mysql, server, user, password, database, 0, 0, 0);
mysql_query(&mysql,"SET NAMES 'UTF8'");

			     	if(conn==NULL){
			     		std::cout<<mysql_error(&mysql)<<std::endl<<std::endl;}
			     	if(conn==NULL){
			     		std::cout<<mysql_error(&mysql)<<std::endl<<std::endl;}



			     	std::string mysql_subscriber_all_table_data = "SELECT c.receive_date,c.source_address,Sum(c.total_bytes)"
			     			"FROM account_database.subscriber AS a INNER JOIN account_database.ip_addresses  AS b "
			     			"INNER JOIN account_database.cal_netflow_data AS c ON a.subscriber_id=b.subscriber_id  "
			     			"WHERE b.ip_address=c.source_address AND full_name='"+changedSubscriberName+"' "
			     			"AND year(c.receive_date)=year(str_to_date('"+ResulYearCombo+"','%Y')) AND month(c.receive_date)=month(str_to_date('"+ResulMonthCombo_index_string+"','%m')) "
			     					"group by DATE_FORMAT(c.receive_date, '%d')";



			     				int row_number = 0;
			     				query_state=mysql_query(conn, mysql_subscriber_all_table_data.c_str());
			     				if(query_state!=0)
			     				{
			     				   std::cout<<mysql_error(conn)<<std::endl<<std::endl;
			     				}
			     				std::string TypeOfcall="";
			     				res=mysql_store_result(conn);
			     				while((row=mysql_fetch_row(res))!=NULL)
			     				{row_number++;


			     				new Wt::WText(Wt::WString::fromUTF8("Netflow трафик"), CHECK_user_treeTablef->elementAt(row_number, 0));
			     				new Wt::WText(Wt::WString::fromUTF8("0.0.0.0"), CHECK_user_treeTablef->elementAt(row_number, 1));
			     				new Wt::WText(Wt::WString::fromUTF8("0"), CHECK_user_treeTablef->elementAt(row_number, 2));
			     				new Wt::WText(Wt::WString::fromUTF8(row[1]), CHECK_user_treeTablef->elementAt(row_number, 3));
			     				new Wt::WText(Wt::WString::fromUTF8("0"), CHECK_user_treeTablef->elementAt(row_number, 4));
			     				new Wt::WText(Wt::WString::fromUTF8("0"), CHECK_user_treeTablef->elementAt(row_number, 5));
			     				new Wt::WText(Wt::WString::fromUTF8(row[0]), CHECK_user_treeTablef->elementAt(row_number, 6));
			     				new Wt::WText(Wt::WString::fromUTF8(row[2]), CHECK_user_treeTablef->elementAt(row_number, 7));
			     				new Wt::WText(Wt::WString::fromUTF8(changedSubscriberName), CHECK_user_treeTablef->elementAt(row_number, 8));

			     				}
			     				CHECK_user_treeTablef->refresh();
			     				mysql_free_result(res);
			     				mysql_close(conn);









				}
					}
					else
									{
										messageBox = new Wt::WMessageBox(Wt::WString::fromUTF8("Ошибка"), Wt::WString::fromUTF8("Не выбран абонент"), Wt::Information, Wt::Yes | Wt::No);
										messageBox->buttonClicked().connect(std::bind([=] () {
										delete messageBox;
										}));

										messageBox->show();
									}


					}


//end of func of showing data (netflow calls)

extern void WtAccounts::Configure_edited_report_data_Report(std::string operation_name){


	if (operation_name=="save"){

		std::ifstream infile("cssQ.txt");
		std::string out3;
		std::stringstream buffer;

		if ( infile )
		{
			buffer << infile.rdbuf();
			infile.close();
			out3=buffer.str();
			// operations on the buffer...
		}


		//	auto itr_text_search;

		std::ofstream out2("output.txt");

std::string Report_edit_temp_string1= out3.substr(out3.find("<!--First_Text-->")+std::string("<!--First_Text-->").length(),out3.find("<!--End_F_Text-->")-(out3.find("<!--First_Text-->")+std::string("<!--First_Text-->").length()));

std::string Report_edit_temp_string2= out3.substr(out3.find("<!--Second_text2-->")+std::string("<!--Second_text2-->").length(),out3.find("<!--End_S_Text2-->")-(out3.find("<!--Second_text2-->")+std::string("<!--Second_text2-->").length()));

out2<<ui->user_text_area_report_edit_1->text().toUTF8();
out2<<std::endl;
out2<<ui->user_text_area_report_edit_2->text().toUTF8();
		//std::ofstream onfile("cssQ.txt");

out2<<std::endl;

		size_t f = out3.find("<!--First_Text-->");
		out3.replace(f+std::string("<!--First_Text-->").length(),Report_edit_temp_string1.length(), ui->user_text_area_report_edit_1->text().toUTF8());
		out2<<f;

		out2<<std::endl;
		f =out3.find("<!--Second_text2-->");
		out2<<f;
		out3.replace(f+std::string("<!--Second_text2-->").length(),Report_edit_temp_string2.length(), ui->user_text_area_report_edit_2->text().toUTF8());
		std::ofstream fout("cssQ.txt");
		fout.write(out3.c_str(), out3.size());
		fout.close();
		out2.close();

		//ui->create_user_tab_mi_report_edit->setHidden(false);
		//ui->main_tabs->setCurrentIndex(3);

		ui->create_user_tab_mi_report_edit->setHidden(true);
		ui->main_tabs->setCurrentIndex(0);

	}


}


//func to make creat report
extern void WtAccounts::p_account_operation_create_Report(std::string operation_name,std::string user_name)
{

	//if (operation_name=="fast") std::cout<<"whats wrong"<<std::endl;
	std::cout<<"OPERATION NAME "<<operation_name<<std::endl;
//
int total_sum=0;
	Wt::WMessageBox *messageBox;

		//check year
		std::string ResulYearCombo="";

		ResulYearCombo=ui->year_combo_box->currentText().toUTF8();

		//check month
		int ResulMonthCombo_index;
		ResulMonthCombo_index=ui->month_combo_box->currentIndex();
		std::string check_date_temp="";

		if (ResulMonthCombo_index==0){
			check_date_temp=std::to_string(std::stoi(ResulYearCombo)-1)+"-12-31";
		}else {
			check_date_temp=ResulYearCombo+"-"+std::to_string(ResulMonthCombo_index)+"-31";
		}
		std::cout<<"Last month for bept for report"<<check_date_temp<<std::endl;
		ResulMonthCombo_index++;
		std::string ResulMonthCombo_index_string=std::to_string(ResulMonthCombo_index);
		std::string ResulMonthCombo_text_string=ui->month_combo_box->currentText().toUTF8();

		std::string ResultOfoperationmeny="";

		//if (operation_name=="fast") std::cout<<"whats wrong15"<<std::endl;

		std::string changedSubscriberName = "";

		Wt::WTreeNode *selected_node; // operator* returns contents of an interator
		std::set<Wt::WTreeNode* > highlightedRows = ui->user_treeTable->tree()->selectedNodes();
		//if (operation_name=="fast") std::cout<<"whats wrong21"<<std::endl;
		if (!highlightedRows.empty() || operation_name=="month"){

			if (operation_name=="month"){
				changedSubscriberName = user_name;
				std::cout<<"REPORT for month for "<<user_name<<std::endl;
				//changedSubscriberName="Амирова Роза Сериковна";}
			}else{
		for (std::set<Wt::WTreeNode* >::iterator i = highlightedRows.begin(); i != highlightedRows.end(); ++i)
									     					{
									     					  selected_node = *i;
									     					}
			changedSubscriberName = selected_node->label()->text().toUTF8();
			}

			//if (operation_name=="fast") std::cout<<"whats wrong22"<<std::endl;

			//creat tab
				Wt::WContainerWidget * CHECK_pop_tab_Temp = new Wt::WContainerWidget(ui->container_cp);
			//	Wt::WMenuItem * CHECK_pop_tab_mi_temp = ui->main_tabs->addTab(CHECK_pop_tab_Temp, Wt::WString::fromUTF8(""));;
			//	Wt::WTable *CHECK_user_treeTablef;
			//	CHECK_pop_tab_mi_temp->setCloseable(true);
			//	CHECK_pop_tab_mi_temp->enable();

			// CHECK_pop_tab_mi_temp->setText(Wt::WString::fromUTF8(ResultOfoperationmeny));

			//ui->main_tabs->setCurrentIndex(ui->main_tabs->indexOf(CHECK_pop_tab_Temp));

			Wt::WContainerWidget *service_table_container = new Wt::WContainerWidget(CHECK_pop_tab_Temp);



			////

			//connect to data base
			mysql_init(&mysql);
			conn=mysql_real_connect(&mysql, server, user, password, database, 0, 0, 0);
			mysql_query(&mysql,"SET NAMES 'UTF8'");

			if(conn==NULL){
			std::cout<<mysql_error(&mysql)<<std::endl<<std::endl;}



			std::string mysql_Data_for_report = "SELECT * FROM  account_database.requisites WHERE subscriber_id IN "
					"(SELECT subscriber_id FROM  account_database.subscriber WHERE full_name = '"+changedSubscriberName+"')";



			query_state=mysql_query(conn, mysql_Data_for_report.c_str());
			// set variables and form elements with data from mysql tables

					if(query_state!=0)
								   {
								 std::cout<<mysql_error(conn)<<std::endl<<std::endl;
								   }
								   res=mysql_store_result(conn);
								    std::cout<<"MySQL Values in the amaDB Table.17 Report"<<std::endl<<std::endl;
								    std::string Presonal_code="";
								    std::string agreement="";
								    if((row=mysql_fetch_row(res))!=NULL) {

								    	if (operation_name=="month"){subscriber_id_view_mode=row[1];}
						     				Presonal_code=row[2];
						     				agreement=row[7];}






			////
			//Use difrent css
		// Add an external style sheet to the application.
		//Wt::WApplication::instance()->useStyleSheet("/resources/Report.css");
		//Wt::WApplication::instance()->useStyleSheet("/resources/fgd.css");
		// The style sheet should be applied to this container only.
		// The class .CSS-example is used as selector.
		//service_table_container->setStyleClass("CSS-example");

			//Wt::WResource *pdf = new ReportResource(service_table_container,5);

				std::ifstream infile("cssQ.txt");
				std::string out3;
				std::stringstream buffer;

		if ( infile )
		{
			buffer << infile.rdbuf();
			infile.close();
			out3=buffer.str();
			// operations on the buffer...
		}


          // infile.open
		size_t f =out3.find("Name_w");
		out3.replace(f,std::string("Name_w").length(), changedSubscriberName);
	    f =out3.find("personal_code");
		out3.replace(f,std::string("personal_code").length(), Presonal_code);

		f =out3.find("req_code");
		out3.replace(f,std::string("req_code").length(), agreement);
	    f =out3.find("req_code");
		out3.replace(f,std::string("req_code").length(), agreement);


		f =out3.find("year_month");
		if (ResulMonthCombo_index_string.length()<2) ResulMonthCombo_index_string.insert (0,"0");
		out3.replace(f,std::string("year_month").length(), ResulYearCombo+ResulMonthCombo_index_string);

		f =out3.find("Report_time1");
		out3.replace(f,std::string("Report_time1").length(), ResulMonthCombo_index_string+"."+ResulYearCombo+"г");

		f =out3.find("month_w");
		out3.replace(f,std::string("month_w").length(), ResulMonthCombo_text_string);

		f =out3.find("year_n");
		out3.replace(f,std::string("year_n").length(), ResulYearCombo);


		if (operation_name=="fast") std::cout<<"whats wrong3"<<std::endl;
		//adress replace
		mysql_free_result(res);
		mysql_Data_for_report = "SELECT street FROM account_database.contacts WHERE subscriber_id "
				"IN (SELECT subscriber_id FROM  account_database.subscriber WHERE full_name = '"+changedSubscriberName+"')";

		query_state=mysql_query(conn, mysql_Data_for_report.c_str());

		if(query_state!=0)
					{
					std::cout<<mysql_error(conn)<<std::endl<<std::endl;
					}
		res=mysql_store_result(conn);
		if((row=mysql_fetch_row(res))!=NULL) {
		std::string Adress_rep=row[0];
		f =out3.find("Adress_");
		out3.replace(f,std::string("Adress_").length(), Adress_rep);}
		mysql_free_result(res);
///
		//Phone number replace
		mysql_Data_for_report = "SELECT number FROM account_database.phone_numbers where subscriber_id='"+subscriber_id_view_mode+"'";

				query_state=mysql_query(conn, mysql_Data_for_report.c_str());

				if(query_state!=0)
							{
							std::cout<<mysql_error(conn)<<std::endl<<std::endl;
							}
				res=mysql_store_result(conn);
				std::string P_numb_rep="";
				if((row=mysql_fetch_row(res))!=NULL) {
				P_numb_rep=row[0];
				}
				f =out3.find("P_number");
				out3.replace(f,std::string("P_number").length(), P_numb_rep);
				mysql_free_result(res);

//		///

		//code for adding service
		        int numberforskip=280;//244 = FULL text size  between <!--ServiceStart--> to <!--ServiceEnd--> (WARRNING depends on size of html part where service add)
				std::string Service = out3.substr(out3.find("<!--ServiceStart-->")+std::string("<!--ServiceStart-->").length(),numberforskip);


				mysql_Data_for_report = "SELECT description,quantity FROM account_database.subscriber_transaction WHERE subscriber_id='"+subscriber_id_view_mode+"'"
						//" IN  (SELECT subscriber_id FROM  account_database.subscriber WHERE full_name = '"+changedSubscriberName+"')"
							"AND  month(transaction_date)=month(str_to_date('"+ResulMonthCombo_index_string+"','%m')) AND year(transaction_date)=year(str_to_date('"+ResulYearCombo+"','%Y')) AND transaction_type='Начисление'";
						    int row_number = 0;

						    query_state=mysql_query(conn, mysql_Data_for_report.c_str());
						    // set variables and form elements with data from mysql tables


						    int NubrOffreetabs=122;//Value for blank space(to make both reports more semetric)
						    if(query_state!=0)
						    		{
						    		std::cout<<mysql_error(conn)<<std::endl<<std::endl;
						    		}

						    res=mysql_store_result(conn);
						    numberforskip=0;

						    std::cout<<"MySQL Values in the amaDB Table.18 Report2"<<std::endl<<std::endl;

						    if((row=mysql_fetch_row(res))!=NULL) {


						   f = out3.find("ServiceName");
						   out3.replace(f,std::string("ServiceName").length(), row[0]);

						   f = out3.find("ServicePrice");
						   out3.replace(f,std::string("ServicePrice").length(), row[1]);
						   total_sum+=std::atoi(row[1]);

						   std::cout<<"MySQL Values in the amaDB Table.19 "<<row[0]<<std::endl<<std::endl;


						    //if more than 1
							while((row=mysql_fetch_row(res))!=NULL)
							{row_number++;
							NubrOffreetabs-=34;//if we add service delete more blank space

									     	std::string TempLength1=row[0];
									     	std::string TempLength2=row[1];
									     	total_sum+=std::atoi(row[1]);

									     	TempLength1+=TempLength2;
									     	std::string ServiceTemp=Service;

									     	f =ServiceTemp.find("ServiceName");
									     	ServiceTemp.replace(f,std::string("ServiceName").length(), row[0]);

									     	f =ServiceTemp.find("ServicePrice");
									     	ServiceTemp.replace(f,std::string("ServicePrice").length(), row[1]);

							out3.insert(out3.find("<!--ServiceEnd-->")+std::string("<!--ServiceEnd-->").length()+numberforskip,ServiceTemp);
							numberforskip+=256+TempLength1.length()+1;//220 is size of pure HTML wiout any text + text that we added to skip forvard
									     				}

									      mysql_free_result(res);

									      double debt_cost=0;
									      double debt_last_mouth=0;
									      double paid_this_month=0;
									      std::string Sum_to_this_mouth="";

									      Sum_to_this_mouth = "SELECT sum(quantity) FROM account_database.subscriber_transaction where subscriber_id ='"+subscriber_id_view_mode+"'  and  transaction_date between '2014-02-03' and str_to_date('"+check_date_temp+"', '%Y-%m-%d') and transaction_type = 'Начисление'";
									      query_state = mysql_query(conn, Sum_to_this_mouth.c_str());
									      if(query_state!=0)
									      {
									    	  std::cout<<mysql_error(conn)<<std::endl<<std::endl;
									      }
									      res=mysql_store_result(conn);

									      if ((row=mysql_fetch_row(res))!=NULL)
									      {
									    	  if (row[0]!=NULL)
									    	  debt_last_mouth=boost::lexical_cast<double>(row[0]);
									    	  mysql_free_result(res);
									      }
                                             std::cout<<std::endl<<" 1 "<<debt_last_mouth<<std::endl;

									      Sum_to_this_mouth = "SELECT sum(quantity) FROM account_database.subscriber_transaction where subscriber_id ='"+subscriber_id_view_mode+"' and transaction_date between '2014-02-03' and str_to_date('"+check_date_temp+"', '%Y-%m-%d') and transaction_type='Оплата'";
									      query_state = mysql_query(conn, Sum_to_this_mouth.c_str());
									      if(query_state!=0)
									      {
									    	  std::cout<<mysql_error(conn)<<std::endl<<std::endl;
									      }
									      res=mysql_store_result(conn);

									      if ((row=mysql_fetch_row(res))!=NULL)
									      {
									    	  if (row[0]!=NULL)
									    		  debt_last_mouth=debt_last_mouth-boost::lexical_cast<double>(row[0]);
									    	  mysql_free_result(res);
									      }
									      std::cout<<std::endl<<" 2 "<<debt_last_mouth<<std::endl;

									    debt_cost+=debt_last_mouth;
									    debt_cost+=total_sum;

									    Sum_to_this_mouth = "SELECT sum(quantity) FROM account_database.subscriber_transaction WHERE subscriber_id='"+subscriber_id_view_mode+"'"
									    							"AND  month(transaction_date)=month(str_to_date('"+ResulMonthCombo_index_string+"','%m')) AND year(transaction_date)=year(str_to_date('"+ResulYearCombo+"','%Y')) AND transaction_type='Оплата'";

									    query_state = mysql_query(conn, Sum_to_this_mouth.c_str());
									    if(query_state!=0)
									    {
									    	std::cout<<mysql_error(conn)<<std::endl<<std::endl;
									    }
									    res=mysql_store_result(conn);

									    if ((row=mysql_fetch_row(res))!=NULL)
									    {
									    	if (row[0]!=NULL)
									    	paid_this_month=boost::lexical_cast<double>(row[0]);
									    	mysql_free_result(res);
									    }


									    std::cout<<std::endl<<" 3 "<<paid_this_month<<std::endl;

									    mysql_close(conn);


										  f = out3.find("Total_TO_PAY");
										  out3.replace(f, std::string("Total_TO_PAY").length(),std::to_string(total_sum));


										  f = out3.find("COL_2");
										  out3.replace(f, std::string("COL_2").length(), std::to_string(total_sum));


										  f = out3.find("COL_1");
										  out3.replace(f, std::string("COL_1").length(), std::to_string(debt_last_mouth));
										  f = out3.find("COL_3");
										  out3.replace(f, std::string("COL_3").length(), "0");
										  f = out3.find("COL_4");
										  out3.replace(f, std::string("COL_4").length(), std::to_string(paid_this_month));

										  f = out3.find("COL_5");
										  out3.replace(f, std::string("COL_5").length(), std::to_string(debt_cost-paid_this_month));
										  if (debt_cost<0) debt_cost=0;

										  f = out3.find("TT_P");
										  out3.replace(f, std::string("TT_P").length(),std::to_string(total_sum));
										  f = out3.find("TT_P");
										  out3.replace(f, std::string("TT_P").length(),std::to_string(debt_cost-paid_this_month));






						out3+="<div style=\"height: " +std::to_string(NubrOffreetabs)+" px;\">&nbsp;</div>";//add blank space befor next report



				//find formated text of report copy at the end it
 std::string Copytext = out3.substr(out3.find("<!--CopyStart-->")+std::string("<!--CopyStart-->").length(),out3.find("<!--CopyEnd-->")-(out3.find("<!--CopyStart-->")+std::string("<!--CopyStart-->").length()));

		out3+=Copytext+"</div>";//close whole div

//		//OUTput in file to test HTML
//		std::ofstream out2("output.txt");
//		out2 << out3;
//		out2.close();


             //creat pdf with contructor

           //  Wt::WPushButton *button2 = new Wt::WPushButton("Create pdf",service_table_container);
//oleg




			// Wt::WPushButton *tempb;
			  //link to rendered  file
			// tempb->setLink(pdf);

			if (operation_name=="month")
			 {  std::cout<<"Creat Pdf func month 52"<<std::endl;
				 WtAccounts::creat_pdf_monthly(changedSubscriberName,out3);
			 } else
			 {          std::cout<<"Creat Pdf func link 53"<<std::endl;
			 			Wt::WResource *pdf = new ReportResource(service_table_container,changedSubscriberName,out3);
			 			Wt::WApplication::redirect(pdf->url());//link to pdf to download
			 }




				    }
				    else {
				    	 if (operation_name!="month"){//if not auto report form
						messageBox = new Wt::WMessageBox(Wt::WString::fromUTF8("Ошибка"), Wt::WString::fromUTF8("Нет данных по этой дате"), Wt::Information, Wt::Yes | Wt::No);
						messageBox->buttonClicked().connect(std::bind([=] () {
						delete messageBox;
						}));

						messageBox->show();}
					}
						}else
						{   if (operation_name!="month"){//if not auto report form
							messageBox = new Wt::WMessageBox(Wt::WString::fromUTF8("Ошибка"), Wt::WString::fromUTF8("Не выбран абонент"), Wt::Information, Wt::Yes | Wt::No);
							messageBox->buttonClicked().connect(std::bind([=] () {
							delete messageBox;
							}));

							messageBox->show();}
						}


}


//func to make creat report for outside calls
extern void WtAccounts::p_account_outside_call_create_Report_(std::string operation_name)
{


	//
	int total_sum=0;
	double total_talk=0;
		Wt::WMessageBox *messageBox;

			//check year
			std::string ResulYearCombo="";

			ResulYearCombo=ui->year_combo_box->currentText().toUTF8();

			//check month
			int ResulMonthCombo_index;
			ResulMonthCombo_index=ui->month_combo_box->currentIndex();ResulMonthCombo_index++;

			std::string ResulMonthCombo_index_string=std::to_string(ResulMonthCombo_index);
			std::string ResulMonthCombo_text_string=ui->month_combo_box->currentText().toUTF8();

			std::string ResultOfoperationmeny="";



			std::string changedSubscriberName = "";
			Wt::WTreeNode *selected_node; // operator* returns contents of an interator
			std::set<Wt::WTreeNode* > highlightedRows = ui->user_treeTable->tree()->selectedNodes();
			//if (operation_name=="fast") std::cout<<"whats wrong21"<<std::endl;
			if (!highlightedRows.empty())
							{
			//get name that selected
			for (std::set<Wt::WTreeNode* >::iterator i = highlightedRows.begin(); i != highlightedRows.end(); ++i)
										     					{
										     					  selected_node = *i;
										     					}
				changedSubscriberName = selected_node->label()->text().toUTF8();


				//creat tab
				Wt::WContainerWidget * CHECK_pop_tab_Temp = new Wt::WContainerWidget(ui->container_cp);


				Wt::WContainerWidget *service_table_container = new Wt::WContainerWidget(CHECK_pop_tab_Temp);



				////

				//connect to data base
				mysql_init(&mysql);
				conn=mysql_real_connect(&mysql, server, user, password, database, 0, 0, 0);
				mysql_query(&mysql,"SET NAMES 'UTF8'");

				if(conn==NULL){
				std::cout<<mysql_error(&mysql)<<std::endl<<std::endl;}



					std::ifstream infile("T_calls.txt");
					std::string out3;
					std::stringstream buffer;

			if ( infile )
			{
				buffer << infile.rdbuf();
				infile.close();
				out3=buffer.str();
				// operations on the buffer...
			}


	          // infile.open
			size_t f =out3.find("Abonent");
			out3.replace(f,std::string("Abonent").length(), changedSubscriberName);

			f =out3.find("time");
			out3.replace(f,std::string("time").length(), ResulMonthCombo_index_string+"."+ResulYearCombo+"г");




			std::string  mysql_Data_for_report = "SELECT street FROM account_database.contacts WHERE subscriber_id "
					"IN (SELECT subscriber_id FROM  account_database.subscriber WHERE full_name = '"+changedSubscriberName+"')";

			query_state=mysql_query(conn, mysql_Data_for_report.c_str());

			if(query_state!=0)
						{
						std::cout<<mysql_error(conn)<<std::endl<<std::endl;
						}
			res=mysql_store_result(conn);
			if((row=mysql_fetch_row(res))!=NULL) {
			std::string Adress_rep=row[0];
			f =out3.find("Adress");
			out3.replace(f,std::string("Adress").length(), Adress_rep);}
			mysql_free_result(res);

			//Phone number replace
			mysql_Data_for_report = "SELECT number FROM account_database.phone_numbers where subscriber_id='"+subscriber_id_view_mode+"'";

					query_state=mysql_query(conn, mysql_Data_for_report.c_str());

					if(query_state!=0)
								{
								std::cout<<mysql_error(conn)<<std::endl<<std::endl;
								}
					res=mysql_store_result(conn);
					std::string P_numb_rep="";
					if((row=mysql_fetch_row(res))!=NULL) {
					P_numb_rep=row[0];
					}
					mysql_free_result(res);
					f =out3.find("Number");
					out3.replace(f,std::string("Number").length(), P_numb_rep);
					f =out3.find("tel_number");
					out3.replace(f,std::string("tel_number").length(), P_numb_rep);


					//		///





				mysql_Data_for_report = "SELECT EXISTS(SELECT 1 FROM account_database.ama_data  where numberA='257023' and call_direction='outgoing' and call_type!='')";


							query_state=mysql_query(conn, mysql_Data_for_report.c_str());
					// set variables and form elements with data from mysql tables

					if(query_state!=0)
					{
						std::cout<<mysql_error(conn)<<std::endl<<std::endl;
					}

					res=mysql_store_result(conn);



					if((row=mysql_fetch_row(res))!=NULL) {

						mysql_Data_for_report = "SELECT start_date,start_time,numberB,(milli_second/1000),call_cost FROM account_database.ama_data WHERE numberA='"+P_numb_rep+"'"
								"AND  month(start_date)=month(str_to_date('"+ResulMonthCombo_index_string+"','%m')) AND year(start_date)=year(str_to_date('"+ResulYearCombo+"','%Y')) AND call_direction='outgoing' AND call_type='inner'";


						query_state=mysql_query(conn, mysql_Data_for_report.c_str());
						// set variables and form elements with data from mysql tables

						if(query_state!=0)
						{
							std::cout<<mysql_error(conn)<<std::endl<<std::endl;
						}

						res=mysql_store_result(conn);
						int numberforskip=479;//244 = FULL text size  between <!--ServiceStart--> to <!--ServiceEnd--> (WARRNING depends on size of html part where service add)
						if((row=mysql_fetch_row(res))!=NULL) {

							//code for adding service

							std::string Service = out3.substr(out3.find("<!--ServiceStar1-->")+std::string("<!--ServiceStar1-->").length(),numberforskip);


							f = out3.find("Row1");
							out3.replace(f,std::string("Row1").length(), row[0]);

							f = out3.find("Row2");
							out3.replace(f,std::string("Row2").length(), row[1]);

							f = out3.find("Row3");
							out3.replace(f,std::string("Row3").length(), row[2]);

							f = out3.find("Row4");
							out3.replace(f,std::string("Row4").length(), "0");

							f = out3.find("Row5");
							out3.replace(f,std::string("Row5").length(), row[3]);
							total_talk+=std::atof(row[3]);

							f = out3.find("Row6");
							out3.replace(f,std::string("Row6").length(), row[4]);



							std::cout<<"MySQL Values in the amaDB Table.20 "<<row[0]<<std::endl<<std::endl;


							//if more than 1
							numberforskip=0;
							std::string Bds="";
							while((row=mysql_fetch_row(res))!=NULL)
							{

							std::string TempLength1=row[0];
							std::string TempLength2=row[1];
							std::string TempLength3=row[2];
							std::string TempLength4=row[3];
							std::string TempLength5=row[4];
							total_talk+=std::atof(row[3]);

							TempLength1+=TempLength2+TempLength3+TempLength4;
							std::string ServiceTemp=Service;

							f =ServiceTemp.find("Row1");
							ServiceTemp.replace(f,std::string("Row1").length(), row[0]);

							f =ServiceTemp.find("Row2");
							ServiceTemp.replace(f,std::string("Row2").length(), row[1]);
							f =ServiceTemp.find("Row3");
							ServiceTemp.replace(f,std::string("Row3").length(), row[2]);
							f =ServiceTemp.find("Row4");
							ServiceTemp.replace(f,std::string("Row4").length(), "0");
							f =ServiceTemp.find("Row5");
							ServiceTemp.replace(f,std::string("Row5").length(), row[3]);
							f =ServiceTemp.find("Row6");
							ServiceTemp.replace(f,std::string("Row6").length(), row[4]);




							Bds+=ServiceTemp;
							out3.insert(out3.find("<!--ServiceEn1-->")+std::string("<!--ServiceEn1-->").length()+numberforskip,ServiceTemp);
							numberforskip+=460+TempLength1.length()+1+1;//220 is size of pure HTML wiout any text + text that we added to skip forvard
							}
							mysql_free_result(res);
							f =out3.find("Total_C2");
							double integral;
							double fractional = std::modf(total_talk, &integral);
							if (fractional>0) total_talk=integral+1;
							out3.replace(f,std::string("Total_C2").length(), std::to_string(int(total_talk)));
							f =out3.find("Total_P2");
							out3.replace(f,std::string("Total_P2").length(), "0");


						} else std::string Service = out3.erase(out3.find("<!--ServiceStar1-->")+std::string("<!--ServiceStar1-->").length(),numberforskip);



						mysql_Data_for_report = "SELECT start_date,start_time,numberB,(milli_second/1000),call_cost FROM account_database.ama_data WHERE numberA='"+P_numb_rep+"'"
								"AND  month(start_date)=month(str_to_date('"+ResulMonthCombo_index_string+"','%m')) AND year(start_date)=year(str_to_date('"+ResulYearCombo+"','%Y')) AND call_direction='outgoing' AND call_type!='inner' AND call_type!=''";


						query_state=mysql_query(conn, mysql_Data_for_report.c_str());
						// set variables and form elements with data from mysql tables

						if(query_state!=0)
						{
							std::cout<<mysql_error(conn)<<std::endl<<std::endl;
						}

						res=mysql_store_result(conn);
						numberforskip=479;//244 = FULL text size  between <!--ServiceStart--> to <!--ServiceEnd--> (WARRNING depends on size of html part where service add)
						if((row=mysql_fetch_row(res))!=NULL) {

							//code for adding service

							std::string Service = out3.substr(out3.find("<!--ServiceStart-->")+std::string("<!--ServiceStart-->").length(),numberforskip);


							f = out3.find("RoP1");
							out3.replace(f,std::string("RoP1").length(), row[0]);

							f = out3.find("RoP2");
							out3.replace(f,std::string("RoP2").length(), row[1]);

							f = out3.find("RoP3");
							out3.replace(f,std::string("RoP3").length(), row[2]);

							f = out3.find("RoP4");
							out3.replace(f,std::string("RoP4").length(), "0");

							f = out3.find("RoP5");
							out3.replace(f,std::string("RoP5").length(), row[3]);
							total_talk+=std::atoi(row[3]);

							f = out3.find("RoP6");
							out3.replace(f,std::string("RoP6").length(), row[4]);



							std::cout<<"MySQL Values in the amaDB Table.21 "<<row[0]<<std::endl<<std::endl;


							//if more than 1
							numberforskip=0;
							total_talk=0;
							total_sum=0;
							std::string Bds="";
							while((row=mysql_fetch_row(res))!=NULL)
							{

								std::string TempLength1=row[0];
								std::string TempLength2=row[1];
								std::string TempLength3=row[2];
								std::string TempLength4=row[3];
								std::string TempLength5=row[4];
								total_talk+=std::atoi(row[3]);
								total_sum+=std::atoi(row[4]);
								TempLength1+=TempLength2+TempLength3+TempLength4;
								std::string ServiceTemp=Service;

								f =ServiceTemp.find("RoP1");
								ServiceTemp.replace(f,std::string("RoP1").length(), row[0]);

								f =ServiceTemp.find("RoP2");
								ServiceTemp.replace(f,std::string("RoP2").length(), row[1]);
								f =ServiceTemp.find("RoP3");
								ServiceTemp.replace(f,std::string("RoP3").length(), row[2]);
								f =ServiceTemp.find("RoP4");
								ServiceTemp.replace(f,std::string("RoP4").length(), "0");
								f =ServiceTemp.find("RoP5");
								ServiceTemp.replace(f,std::string("RoP5").length(), row[3]);
								f =ServiceTemp.find("RoP6");
								ServiceTemp.replace(f,std::string("RoP6").length(), row[4]);




								Bds+=ServiceTemp;
								out3.insert(out3.find("<!--ServiceStart-->")+std::string("<!--ServiceStart-->").length()+numberforskip,ServiceTemp);
								numberforskip+=460+TempLength1.length()+1+1;//220 is size of pure HTML wiout any text + text that we added to skip forvard
							}


							mysql_free_result(res);

							f =out3.find("Total_C1");
							out3.replace(f,std::string("Total_C1").length(), std::to_string(total_talk));
							f =out3.find("Total_P1");
							out3.replace(f,std::string("Total_P1").length(), std::to_string(total_sum));
							f =out3.find("Total_P");
							out3.replace(f,std::string("Total_P").length(), std::to_string(total_sum));

						} else {std::string Service = out3.erase(out3.find("<!--ServiceStart-->")+std::string("<!--ServiceStart-->").length(),numberforskip);
						f =out3.find("Total_C1");
						out3.replace(f,std::string("Total_C1").length(), "0");
						f =out3.find("Total_P1");
						out3.replace(f,std::string("Total_P1").length(), "0");
						f =out3.find("Total_P");
						out3.replace(f,std::string("Total_P").length(), "0");

						}






					}

//					//OUTput in file to test HTML
//					std::ofstream out2("output.txt");
//					out2 << out3;
//					out2.close();



	             //creat pdf with contructor
				Wt::WResource *pdf = new ReportResource(service_table_container,changedSubscriberName,out3);

				  //link to rendered  file
				 Wt::WApplication::redirect(pdf->url());//link to pdf to download


//					    }
//					    else {
//							messageBox = new Wt::WMessageBox(Wt::WString::fromUTF8("Ошибка"), Wt::WString::fromUTF8("Нет данных по этой дате"), Wt::Information, Wt::Yes | Wt::No);
//							messageBox->buttonClicked().connect(std::bind([=] () {
//							delete messageBox;
//							}));
//
//							messageBox->show();
//						}
							}else
							{
								messageBox = new Wt::WMessageBox(Wt::WString::fromUTF8("Ошибка"), Wt::WString::fromUTF8("Не выбран абонент"), Wt::Information, Wt::Yes | Wt::No);
								messageBox->buttonClicked().connect(std::bind([=] () {
								delete messageBox;
								}));

								messageBox->show();
							}





}
//func to make report
extern void WtAccounts::p_account_operation_Report(std::string operation_name)
{


// show dialog window where you manage reports (create)



	    Wt::WDialog *dialog = new Wt::WDialog(Wt::WString::fromUTF8("Отчеты"));

	    dialog->resize(500, 300);

Wt::WPushButton *save_exit_button = new Wt::WPushButton(Wt::WString::fromUTF8("Квитанция для физ."), dialog->contents());
	        //save_exit_button->setStyleClass(Wt::WString::fromUTF8("btn btn-default with-label col-md-3 col-lg-3"));

Wt::WPushButton *add_service_button = new Wt::WPushButton(Wt::WString::fromUTF8("Редактирование квитанции"), dialog->contents());
	        //add_service_button->setStyleClass(Wt::WString::fromUTF8("btn btn-default with-label col-md-3 col-lg-3"));

Wt::WPushButton *add2_service_button = new Wt::WPushButton(Wt::WString::fromUTF8("Расшифровка город и межгород"), dialog->contents());
	              //  add_service_button->setStyleClass(Wt::WString::fromUTF8("btn btn-default with-label col-md-3 col-lg-3"));

	                dialog->show();

	                Wt::WPushButton *cancel = new Wt::WPushButton(Wt::WString::fromUTF8("Закрыть"), dialog->footer());
	                    dialog->rejectWhenEscapePressed();


	                    // Accept the dialog
	                //    save_exit_button->setLink()
	                    save_exit_button->clicked().connect(std::bind([=] () {
	                      WtAccounts::p_account_operation_create_Report("edit","");

	                       dor=1;dialog->accept();delete dialog;
	                    }));

	                    add_service_button->clicked().connect(std::bind([=] () {
	                    	 // WtAccounts::subscriber_show_operation_tab("view");

//herdre
	                    	ui->create_user_tab_mi_report_edit->setHidden(false);
	                    	ui->main_tabs->setCurrentIndex(3);

	                		std::ifstream infile("cssQ.txt");
	                		std::string out3="";
	                		std::stringstream buffer;

	                		if ( infile )
	                		{
	                			buffer << infile.rdbuf();
	                			infile.close();
	                			out3=buffer.str();
	                			// operations on the buffer...
	                		}
	                		std::string temp_text_report_edit1="";
	                		std::string temp_text_report_edit2="";
	                	//	auto itr_text_search;
	                		auto temp_lenth=std::string("<!--First_Text-->").length();


	                			//std::ofstream out2("output.txt");



	                		//find find place of first keyword->copy from it and sub  its lenth.
	                		//second arument is how much to copy  -> ( we find second keyword and sub from it  iterator place of  first  keywod to get length just text between
	temp_text_report_edit1 = out3.substr(out3.find("<!--First_Text-->")+std::string("<!--First_Text-->").length(),out3.find("<!--End_F_Text-->")-(out3.find("<!--First_Text-->")+std::string("<!--First_Text-->").length()));

  //  out2<<temp_text_report_edit1;
	ui->user_text_area_report_edit_1->setText(Wt::WString::fromUTF8(temp_text_report_edit1));

	temp_text_report_edit2 = out3.substr(out3.find("<!--Second_text2-->")+std::string("<!--Second_text2-->").length(),out3.find("<!--End_S_Text2-->")-(out3.find("<!--Second_text2-->")+std::string("<!--Second_text2-->").length()));
	//out2<<temp_text_report_edit2;

	ui->user_text_area_report_edit_2->setText(Wt::WString::fromUTF8(temp_text_report_edit2));

	// out2.close();






	                    	  dor=2;dialog->accept();delete dialog;
                         }));

	                    add2_service_button->clicked().connect(std::bind([=] () {
	                    	//RAJ
	                    	WtAccounts::p_account_outside_call_create_Report_("create");    dor=3;dialog->accept();delete dialog;
	                    }));

	                    // Reject the dialog
	                    cancel->clicked().connect(dialog, &Wt::WDialog::reject);


	                    // Process the dialog result.
	                    /*
	                    dialog->finished().connect(std::bind([=] () {
	                	if (dor==1)      {}
	                	else if (dor==2) {}
	                	else if (dor==3) {}
	                	else if (dor==0) {}
	                	dor==0;
	                    }));*/

}

// function for operation on check
extern void WtAccounts::p_account_operation_CHECK(std::string operation_name)
{
	Wt::WMessageBox *messageBox;

//get name of Menu that pressed
std::string ResultOfoperationmeny="";
ResultOfoperationmeny=ui->p_account_operation_split_button_popup->result()->text().toUTF8();

std::set<Wt::WTreeNode* > highlightedRows = ui->user_treeTable->tree()->selectedNodes();
//if (!highlightedRows.empty()){}

//Trafic and net flow depend on user that selected t we check if any user selected first inside func



if (Wt::WString::fromUTF8("Телефонный трафик")==Wt::WString::fromUTF8(ResultOfoperationmeny) || Wt::WString::fromUTF8("Netflow трафик")==Wt::WString::fromUTF8(ResultOfoperationmeny)){
	p_account_operation_Data("Телефонный трафик");
}

//Generate report ( check if user selected  inside func)
if (Wt::WString::fromUTF8("Новый отчет")==Wt::WString::fromUTF8(ResultOfoperationmeny)){
	WtAccounts::p_account_operation_create_Report("edit","");}

if (Wt::WString::fromUTF8("Создать отчет")==Wt::WString::fromUTF8(ResultOfoperationmeny)){
				p_account_operation_Report("Новый отчет");}


}

//send report to all users with mail


///
extern void WtAccounts::send_mail_to_users(){
  std::string abonent_name="";
  std::string mail_adress="";
  FILE* hFile=NULL;
	try {

	mysql_init(&mysql);
	conn=mysql_real_connect(&mysql, server, user, password, database, 0, 0, 0);
	if(conn==NULL)
	{
		std::cout<<mysql_error(&mysql)<<std::endl<<std::endl;
	}
	mysql_query(&mysql,"SET NAMES 'UTF8'");


	std::string mysql_Data_for_report = "SELECT full_name,user_email FROM account_database.subscriber where user_email!=''";

	query_state=mysql_query(conn, mysql_Data_for_report.c_str());
	if(query_state!=0)
	{
		std::cout<<mysql_error(conn)<<std::endl<<std::endl;
	}
	res_mail=mysql_store_result(conn);
	while((row_mail=mysql_fetch_row(res_mail))!=NULL)
			{
		abonent_name=boost::lexical_cast<std::string>(row_mail[0]);
		mail_adress=boost::lexical_cast<std::string>(row_mail[1]);

		std::string patch="/home/judge/Documents/";
		patch+=abonent_name+".pdf";
//.substr(0,2)+
		std::cout<<"Wait 1"<<patch<<std::endl;
		std::cout<<"Wait 2"<<mail_adress<<std::endl;


		WtAccounts::p_account_operation_create_Report("month",abonent_name);
		//usleep(1000000);
		        hFile = fopen(patch.c_str(),"rb");
		        if(!hFile) {
		             std::cout << "File not found 245" << std::endl;
		        }else {
		        WtAccounts::send_email("esep@automation-trade.com",mail_adress,"Квитанция.pdf",patch);
		        fclose(hFile);}




		std::cout<<"End of WAIT3 "<<mail_adress<<std::endl;
	}
	mysql_free_result(res_mail);
	mysql_close(conn);

	std::cout<<"start sending to "<<mail_adress<<std::endl;



	std::cout<<"end send"<<std::endl;

} catch (const std::exception& e) {std::cout <<"Creat report -> "<< e.what()<<std::endl;}
}
///
// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
