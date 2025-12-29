#ifdef __cplusplus
extern "C" {
#endif

#ifndef _HTTP_H_
#define _HTTP_H_

#include "main.h"

/////////////////
// HTTP server //
/////////////////
#define HTTP_PORT               80
#define HTTP_RX_MAX_CONF        15

#define HTTP_CONNECTION_TIMEOUT   3000
#define HTTP_RX_TIMEOUT           50

#define HTTP_SERVER_INIT          0
#define HTTP_SERVER_ON            1

#define HTTP_CLIENT_INIT          0
#define HTTP_CLIENT_CONNECTED     1
#define HTTP_CLIENT_ON_RX         2
#define HTTP_CLIENT_ON_ANALYSIS   3
#define HTTP_CLIENT_ON_TX         4

/*
#define JSON_TICK      100
*/

const char cssSTYLE[] =
  ".myform { width:450px;padding:30px;margin:40px auto;background: #FFF; border-radius: 10px; -webkit-border-radius:10px; -moz-border-radius: 10px; box-shadow: 0px 0px 10px rgba(0, 0, 0, 0.13); -moz-box-shadow: 0px 0px 10px rgba(0, 0, 0, 0.13); -webkit-box-shadow: 0px 0px 10px rgba(0, 0, 0, 0.13); }"               
  ".myform .inner-wrap{ padding: 30px;background: #F8F8F8; border-radius: 6px; margin-bottom: 15px; }"
  ".myform h1{background: #2A88AD;padding: 20px 30px 15px 30px;margin: -30px -30px 30px -30px;border-radius: 10px 10px 0 0;-webkit-border-radius: 10px 10px 0 0;-moz-border-radius: 10px 10px 0 0;color: #fff;text-shadow: 1px 1px 3px rgba(0, 0, 0, 0.12);font: normal 30px Arial, Helvetica;-moz-box-shadow: inset 0px 2px 2px 0px rgba(255, 255, 255, 0.17);-webkit-box-shadow: inset 0px 2px 2px 0px rgba(255, 255, 255, 0.17);box-shadow: inset 0px 2px 2px 0px rgba(255, 255, 255, 0.17);border: 1px solid #257C9E; }"
  ".myform h1 > span{display: block;margin-top: 2px;font: 13px Arial, Helvetica, sans-serif;}"
  ".myform label{display: block;font: 13px Arial, Helvetica, sans-serif;color: #888;margin-bottom: 15px;}"
  ".myform input[type='text'], .myform input[type='date'], .myform input[type='datetime'], .myform input[type='email'], .myform input[type='number'], .myform input[type='search'], .myform input[type='time'], .myform input[type='url'], .myform input[type='password'], .myform textarea, .myform select {display: block; box-sizing: border-box; -webkit-box-sizing: border-box; -moz-box-sizing: border-box; width: 100%; padding: 8px; border-radius: 6px; -webkit-border-radius:6px; -moz-border-radius:6px; border: 2px solid #fff; box-shadow: inset 0px 1px 1px rgba(0, 0, 0, 0.33); -moz-box-shadow: inset 0px 1px 1px rgba(0, 0, 0, 0.33); -webkit-box-shadow: inset 0px 1px 1px rgba(0, 0, 0, 0.33); }"
  ".two-fields input { width:20% !important; }"
  ".center {text-align: center;}"
  ".myform .section{font: normal 20px Arial, Helvetica;color: #2A88AD;margin-bottom: 5px;}"             
  ".myform .section span {background: #2A88AD;padding: 5px 10px 5px 10px;position: absolute;border-radius: 50%;-webkit-border-radius: 50%;-moz-border-radius: 50%;border: 4px solid #fff;font-size: 14px;margin-left: -45px;color: #fff;margin-top: -3px;}"
  ".myform .m0 {display:inline;background: #000000;padding: 5px 10px 5px 10px;margin-left: 5px;margin-right: 10px;border-radius: 50%;-webkit-border-radius: 50%;-moz-border-radius: 50%;border: 4px solid #fff;font-size: 14px;color: #fff;}"
  ".myform .m1 {display:inline;background: #0BA606;padding: 5px 10px 5px 10px;margin-left: 5px;margin-right: 10px;border-radius: 50%;-webkit-border-radius: 50%;-moz-border-radius: 50%;border: 4px solid #fff;font-size: 14px;color: #fff;}"
  ".myform input[type='button'], .myform input[type='submit']{background: #2A88AD;padding: 8px 20px 8px 20px;border-radius: 5px;-webkit-border-radius: 5px;-moz-border-radius: 5px;color: #fff;text-shadow: 1px 1px 3px rgba(0, 0, 0, 0.12);font: normal 30px Arial, Helvetica;-moz-box-shadow: inset 0px 2px 2px 0px rgba(255, 255, 255, 0.17);-webkit-box-shadow: inset 0px 2px 2px 0px rgba(255, 255, 255, 0.17);box-shadow: inset 0px 2px 2px 0px rgba(255, 255, 255, 0.17);border: 1px solid #257C9E;font-size: 15px;}"
  ".myform input[type='button']:hover, .myform input[type='submit']:hover{background: #2A6881;-moz-box-shadow: inset 0px 2px 2px 0px rgba(255, 255, 255, 0.28);-webkit-box-shadow: inset 0px 2px 2px 0px rgba(255, 255, 255, 0.28);box-shadow: inset 0px 2px 2px 0px rgba(255, 255, 255, 0.28);}"
  ".myform .privacy-policy{float: right;width: 250px;font: 12px Arial, Helvetica, sans-serif;color: #4D4D4D;margin-top: 10px;text-align: right;}"
  ".sansserif {font-family: Arial, Helvetica, sans-serif;}";

#endif // _HTTP_H_

#ifdef __cplusplus
} // extern "C"
#endif
