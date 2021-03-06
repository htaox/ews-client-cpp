#pragma once

#ifndef EWS_CLIENT_H
#define EWS_CLIENT_H

#include "durian.h"
#include "ews-client-global.h"
//using namespace SimpleSoap;

namespace ews {
  namespace client {

    namespace XmlElement {
      class Root;
    }

    template<typename xmlelement>
    class base {
    public:
      base(){}
      ~base(){}
      std::string tpl;

      template<typename T>
      string compile(const shared_ptr<T> o){

        //read entire template file 
        std::ifstream file(tpl.c_str());
        std::string tplx((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

        if (tplx.size() == 0){
          return "";
        }

        //compile tempplate with context to create a soap message
        Plustache::template_t t;
        std::string result = t.render(tplx, *o);

        return result;
      }
    };

    template<typename xmlelement>
    class generator_impl : public base<xmlelement>{};

    /*
      Root
    */
    template<>
    class generator_impl<XmlElement::Root> : public base<XmlElement::Root>{
    public:
      generator_impl(){ tpl = "tpl/root"; }

    };

    /*
      Other implementations below
      See here: https://msdn.microsoft.com/en-us/library/aa580675(v=exchg.80).aspx
    */

  }
}

#endif