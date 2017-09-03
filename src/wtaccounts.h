/*
 * wtaccounts.h
 *
 *  Created on: Jul 22, 2016
 *      Author: bigbang
 */

#ifndef WTACCOUNTS_H
#define WTACCOUNTS_H

#include <Wt/WApplication>

#include "ui_wtaccounts.h"

class WtAccounts : public Wt::WApplication
{

public:
	WtAccounts(const Wt::WEnvironment& env);
	~WtAccounts();

	// declare slots here
	void data_load_user_account_tab();
	void create_user_tab_save_data();
	void edit_subscriber_load_data();
	// ***
	void subscriber_show_operation_tab(std::string operation_name);
	void subscriber_name_dialog(std::string operation_name);
	void subscriber_group_dialog(std::string operation_name);

	void subscriber_phone_number_dialog(std::string operation_name);
	void create_phone_number_dialog(std::string operation_name);
	void delete_phone_number_dialog(std::string operation_name);

	void subscriber_ip_address_dialog(std::string operation_name);
	void create_ip_address_dialog(std::string operation_name);
	void delete_ip_address_dialog(std::string operation_name);

	void subscriber_service_dialog(std::string operation_name);
	void add_service_dialog(std::string operation_name);
	void delete_service_dialog(std::string operation_name);

	void subscriber_tariff_plan_dialog(std::string operation_name);
	void subscriber_contact_dialog(std::string operation_name);
	void save_data_and_close_tab(std::string operation_name);

	// administrative functions
	// *************************************************************************
	void manage_services_dialog();
	void create_new_service_dialog();
	void manage_new_call_tariff_dialog();
	void create_new_call_tariff_dialog(std::string operation_name,std::string operation_id);
	void create_new_select_tariff_dialog_S(std::string operation_name);
	// void temp_func();
	// *************************************************************************


	void account_operation_popup_item_binder();
	void subscriber_add_one_time_services_dialog();
	void subscriber_payment_transaction_dialog();
	void subscriber_fullName_changed();

	// herdre functions
	// *************************************************************************
	void p_account_operation_CHECK(std::string operation_name);
	//data
	void p_account_operation_Data(std::string operation_name);
	//report
	void p_account_operation_Report(std::string operation_name);
	void p_account_outside_call_create_Report_(std::string operation_name);
	void p_account_operation_create_Report(std::string operation_name);
	void Configure_edited_report_data_Report(std::string operation_name);
	//Serarch
	void search_subscribers(std::string operation_name);
    //check tabs that was closed
	void checkIndex_TAB_close(int);

	void month_button_fastswitch(int);


private:
	Ui_WtAccounts *ui;

};

#endif // WTACCOUNTS_H
