/// \file OnlineRoutes.h
/*
 *
 * OnlineRoutes.h header template automatically generated by a class generator
 * Creation date : mer. juin 17 2015
 *
 * This file is part of DQM4HEP libraries.
 * 
 * DQM4HEP is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * based upon these libraries are permitted. Any copy of these libraries
 * must include this copyright notice.
 * 
 * DQM4HEP is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with DQM4HEP.  If not, see <http://www.gnu.org/licenses/>.
 * 
 * @author Remi Ete
 * @copyright CNRS , IPNL
 */


#ifndef DQM4HEP_ONLINEROUTES_H
#define DQM4HEP_ONLINEROUTES_H

// -- dqm4hep headers
#include <dqm4hep/Internal.h>

namespace dqm4hep {

  namespace online {

    /** 
     *  @brief  OnlineRoutes class.
     *          Defines all network routes for the online package 
     */
    class OnlineRoutes {
    public:
      /**
       *  @brief  RunControl class.
       *          Defines the routes related to run control
       */
      class RunControl {
      public:
        /**
         *  @brief  Definition of the status RPC service name
         *
         *  @param  runControlName the run control name
         *  @return the status RPC service name
         */
        static const std::string status(const std::string &runControlName);
        
        /**
         *  @brief  Definition of the SOR service name
         *
         *  @param  runControlName the run control name
         *  @return the SOR service name
         */
        static const std::string sor(const std::string &runControlName);
        
        /**
         *  @brief  Definition of the EOR service name
         *
         *  @param  runControlName the run control name
         *  @return the EOR service name
         */
        static const std::string eor(const std::string &runControlName);
      };

      //-------------------------------------------------------------------------------------------------
      //-------------------------------------------------------------------------------------------------      

      class Application {
      public:
        /**
         *  @brief  Get the server name given an app type and name
         *  
         *  @param  type the app type
         *  @param  name the app name
         */
        static std::string serverName(const std::string &type, const std::string &name);
        
        /**
         *  @brief  Get the app state service name given an app type and name
         *  
         *  @param  type the app type
         *  @param  name the app name
         */
        static std::string state(const std::string &type, const std::string &name);
      };
      
      //-------------------------------------------------------------------------------------------------
      //-------------------------------------------------------------------------------------------------

      class EventCollector {
      public:
        /**
         *  @brief  Get the event collector application type
         */
        static std::string applicationType();
        
        /**
         *  @brief  Get the event collector request name to register a new event source
         * 
         *  @param  collector the collector name
         */
        static std::string registerSource(const std::string &collector);
        
        /**
         *  @brief  Get the event collector command name to unregister a new event source
         * 
         *  @param  collector the collector name
         */
        static std::string unregisterSource(const std::string &collector);
        
        /**
         *  @brief  Get the event collector command name to collect an event
         * 
         *  @param  collector the collector name
         */
        static std::string collectEvent(const std::string &collector);
        
        /**
         *  @brief  Get the event collector service name to receive event updates
         * 
         *  @param  collector the collector name
         *  @param  source the source name
         */
        static std::string eventUpdate(const std::string &collector, const std::string &source);
        
        /**
         *  @brief  Get the event collector request name to receive event on query
         * 
         *  @param  collector the collector name
         */
        static std::string eventRequest(const std::string &collector);
      };

      //-------------------------------------------------------------------------------------------------
      //-------------------------------------------------------------------------------------------------
      
      /**
       *  @brief  OnlineManager class
       *          Defines routes related to the online manager server
       */
      class OnlineManager {
      public:
        /**
         *  @brief  Get the online manager server name
         */
        static const std::string serverName();
        
        /**
         *  @brief  Get the name of the service that sends (server) or receives (client) logs 
         */
        static const std::string logs();

        /**
         *  @brief  Get the name of the service that sends (server) or receive (client) app statistics
         */
        static const std::string appStats();
        
        /**
         *  @brief  Get the name of the commmand to send (client) or collect (server) a log message
         */
        static const std::string collectLog();
        
        /**
         *  @brief  Get the name of the commmand to send (client) or collect (server) an app statistics
         */
        static const std::string collectAppStat();
      };
      
      //-------------------------------------------------------------------------------------------------
      //-------------------------------------------------------------------------------------------------
      
      /**
      *  @brief  ModuleApplication class
      *          Defines routes related to module application
       */
      class ModuleApplication {
      public:
        /**
         *  @brief  Get the application type
         */
        static const std::string applicationType();
        
        /**
         *  @brief  Get the name of the command to receive (module) or send (client) a 
         *          new monitor element subscription list 
         *          
         *  @param  moduleName the module name of the aplication
         */
        static const std::string subscribe(const std::string &moduleName);
      };
    };

  }

} 

#endif  //  DQM4HEP_ONLINEROUTES_H
