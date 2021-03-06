/// \file DQMApplication.h
/*
 *
 * DQMApplication.h header template automatically generated by a class generator
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


#ifndef DQM4HEP_APPLICATION_H
#define DQM4HEP_APPLICATION_H

// -- dqm4hep headers
#include "dqm4hep/Internal.h"
#include "dqm4hep/Server.h"
#include "dqm4hep/Client.h"
#include "dqm4hep/AppEvent.h"
#include "dqm4hep/AppEvents.h"
#include "dqm4hep/AppEventLoop.h"
#include "dqm4hep/Logger.h"

namespace dqm4hep {

  namespace online {

    /** 
     *  @brief  Application class
     */
    class Application {
    public:  
      /**
       *  @brief  Default constructor
       */
      Application() = default;
      Application(const Application&) = delete;
      Application& operator=(const Application&) = delete;
      
      /** 
       *  @brief  Destructor
       */
      virtual ~Application();

      /** 
       *  @brief  Parse the command line arguments.
       *          After parsing the cmd line, the application must provide
       *          a valid type and name. At this step the server is not yet created. 
       *
       *  @param  argc the argc argument from the main function
       *  @param  argc the argv argument from the main function
       */
      virtual void parseCmdLine(int argc, char **argv) = 0;
      
      /** 
       *  @brief  Custom application initialization function. At this step the 
       *          server is created but is not yet running.
       *          This is the place where the application should create:
       *            - all needed services 
       *            - all stats entries
       */
      virtual void onInit() = 0;
      
      /**
       *  @brief  Process an event from the event loop 
       *  
       *  @param  pAppEvent the event to process
       */
      virtual void onEvent(AppEvent *pAppEvent) = 0;
      
      /**
       *  @brief  Custom user function called just before starting the event loop.
       *          At this step the internal server is already running.
       *          This function may e.g send an initial event to the event loop.
       */
      virtual void onStart() = 0;
      
      /**
       *  @brief  Custom user function called just after exiting the event loop.
       */
      virtual void onStop() = 0;

      /** 
       *  @brief  Get the application type
       */
      const std::string &type() const;
      
      /** 
       *  @brief  Set the application type.
       *          Throw exception if called after init() is called
       *
       *  @param  type the application type
       */
      void setType(const std::string &type);

      /** 
       *  @brief  Get the application name
       */
      const std::string &name() const;
      
      /** 
       *  @brief  Set the application name
       *          Throw exception if called after init() is called
       *
       *  @param  name the application name
       */
      void setName(const std::string &name);
      
      /**
       *  @brief  Get the application state
       */
      const std::string &state() const;
      
      /**
       *  @brief  Change the application state
       *
       *  @param  state the new application state
       */
      void setState(const std::string &state);
      
      /**
       *  @brief  Get the application log level
       */
      core::Logger::Level logLevel() const;
      
      /**
       *  @brief  Get the application log level
       *
       *  @param  lvl the new logging level
       */
      void setLogLevel(core::Logger::Level lvl);
      
      /**
       *  @brief  Create a statistics entry.
       *  
       *  @param  name the stat entry name
       *  @param  unit the stat entry unit
       *  @param  description the stat entry description
       */
      void createStatsEntry(const std::string &name, const std::string &unit, const std::string &description);
      
      /**
       *  @brief  Send the stat entry with a new value
       *
       *  @param  name the stat entry name
       *  @param  stats the new stat value
       */
      void sendStat(const std::string &name, double stats);
      
      /**
       *  @brief  Set whether to send statistics on update
       *  
       *  @param  enable whether to enable application stats
       */
      void enableStats(bool enable);
      
      /**
       *  @brief  Whether the statistics are enabled
       */
      bool statsEnabled() const;
      
      /**
       *  @brief  Enable or disable running the application server.
       *
       *  Some application might not need to setup a server to run
       *  and can be disabled by calling setNoServer(true) in the ctor or in parseCmdLine()
       *  
       *  @param  nosrv whether to enable / disable the server 
       */
      void setNoServer(bool nosrv);
      
      /**
       *  @brief  Whether the server has been disabled
       */
      bool noServer() const;
      
      /**
       *  @brief  Initialize the application.
       *          Calls userInit()
       *  
       *  @param  argc the argc from the main function
       *  @param  argv the argv from the main function
       */
      void init(int argc, char **argv);
      
      /** 
       *  @brief  Run the application
       */
      int exec();

      /** 
       *  @brief  Exit the application with the specified return code
       *          If the application is running with exec(), exec will return the specified code
       *
       *  @param  returnCode the code to return from exec() 
       */
      void exit(int returnCode);
      
      /**
       *  @brief  Whether the application has been initialized
       */
      bool initialized() const;
      
      /**
       *  @brief  Whether the application is running
       */
      bool running() const;
      
      /// Client interface
      /**
       *  @brief  Send a request using the net client interface. 
       *          See net::Client class.
       *  
       *  @param  name the command name
       *  @param  contents the command contents to send
       *  @param  blocking whether to receive aknowledgment while send the command
       */
      template <typename T>
      void sendCommand(const std::string &name, const T &contents, bool blocking = false) const;
      
      /**
       *  @brief  Send a request using the net client interface. 
       *          See net::Client class.
       *
       *  @param  name the request name
       *  @param  request the buffer to send
       *  @param  operation the operation to perform on answer reception 
       */
      template <typename Operation>
      void sendRequest(const std::string &name, const net::Buffer &request, Operation operation);
      
      /**
       *  @brief  Subscribe to service. On service update, the content is posted
       *          using the postEvent() function with a ServiceUpdateEvent event.
       *          The received service buffer is copied and can be accessed using
       *          the method ServiceUpdateEvent::buffer() in the callback method
       *          Application::onEvent(). A maximum limit of posted event from the 
       *          service can be set using the argument maxNEvents. If this limit
       *          is reached, the service update is not posted.
       *  
       *  @param  serviceName the service name to subscribe
       *  @param  priority the priority of the event in the event queue
       *  @param  maxNEvents the maximum number of updates for this service to post
       */
      void queuedSubscribe(const std::string &serviceName, int priority = 50, int maxNEvents = std::numeric_limits<int>::max());
      
      /**
       *  @brief  Subscribe to service. On service update, the content is posted
       *          using the sendEvent() function with a ServiceUpdateEvent event.
       *          The received service buffer is not copied but directly passed to
       *          the user. The buffer can be accessed using the method 
       *          ServiceUpdateEvent::buffer() in the callback method
       *          Application::onEvent().
       *          ATTN! The server thread will not be released until the event has
       *          been processed by the sendEvent method !
       *  
       *  @param  serviceName the service name to subscribe
       */
      template <typename Controller>
      void directSubscribe(const std::string &serviceName, Controller *controller, void (Controller::*function)(const net::Buffer &));
      
      /// Server interface
      /**
       *  @brief  Create a new service
       *  
       *  @param  name the service name
       */
      net::Service *createService(const std::string &name);
      
      /**
       *  @brief  Create a request handler. On request, the request content is posted
       *          using the sendEvent() function with a RequestEvent event.
       *          The received service buffer is not copied but directly passed to
       *          the user. The request buffer and the response buffer can be accessed 
       *          respectively using the method RequestEvent::request() and 
       *          RequestEvent::response() in the callback method Application::onEvent().
       *          ATTN! The server thread will not be released until the event has
       *          been processed by the sendEvent method !
       *  
       *  @param requestName the request name to handle
       */
      template <typename Controller>
      void createRequestHandler(const std::string &requestName, Controller *controller, void (Controller::*function)(const net::Buffer &, net::Buffer &));
      
      /**
       *  @brief  Create a command handler. On command reception, the content is posted
       *          using the postEvent() function with a CommandEvent event.
       *          The received service buffer is copied and can be accessed using
       *          the method CommandEvent::buffer() in the callback method
       *          Application::onEvent(). A maximum limit of posted event from the 
       *          command can be set using the argument maxNEvents. If this limit
       *          is reached, the command handling is not posted.
       *  
       *  @param  commandName the command name to handle
       *  @param  priority the priority of the event in the event queue
       *  @param  maxNEvents the maximum number of event for this command to post
       */
      void createQueuedCommand(const std::string &commandName, int priority = 50, int maxNEvents = std::numeric_limits<int>::max());
      
      /**
       *  @brief  Create a command handler. On command reception, the content is posted
       *          using the sendEvent() function with a CommandEvent event.
       *          The received command buffer is not copied but directly passed to
       *          the user. The buffer can be accessed using the method 
       *          CommandEvent::buffer() in the callback method
       *          Application::onEvent().
       *          ATTN! The server thread will not be released until the event has
       *          been processed by the sendEvent method !
       *  
       *  @param commandName the command name to subscribe
       */
      template <typename Controller>
      void createDirectCommand(const std::string &commandName, Controller *controller, void (Controller::*function)(const net::Buffer &));
      
      /**
       *  @brief  Get the current server client id
       */
      int serverClientId() const;

      /**
       *  @brief  Send a client exit event in the event loop 
       * 
       *  @param clientId the client id
       */
      void sendClientExitEvent(int clientId);
      
      /**
       *  @brief  Create a timer synchronized with the event loop
       *          The allocated timer has to be removed by calling removeTimer()
       */
      AppTimer* createTimer();
      
      /**
       *  @brief  Remove timer
       *  
       *  @param timer the timer to remove
       */
      void removeTimer(AppTimer *timer);
      
    private:
      /**
       *  @brief  Send application statistics
       */
      void sendAppStats();
      
      /**
       *  @brief  Create the internal stat entries (memory, CPU, etc ...)
       */
      void createInternalStats();
      
    private:
      /**
       *  @brief  NetworkHandler class
       */
      class NetworkHandler {
      public:
        /**
         *  @brief  Constructor
         *  
         *  @param eventLoop the application event loop
         *  @param name the name of service/command/request to handle
         *  @param priority the event priority, if the event is posted
         */
        NetworkHandler(AppEventLoop &eventLoop, const std::string &name, int priority = 50, int maxNEvents = std::numeric_limits<int>::max());
        
        /**
         *  @brief  Constructor
         *  
         *  @param eventLoop the application event loop
         *  @param name the name of service/command/request to handle
         *  @param priority the event priority, if the event is posted
         */
        template <typename Controller>
        NetworkHandler(AppEventLoop &eventLoop, const std::string &name, Controller *controller, void (Controller::*function)(const net::Buffer &));
        
        /**
         *  @brief  Constructor
         *  
         *  @param eventLoop the application event loop
         *  @param name the name of service/command/request to handle
         *  @param priority the event priority, if the event is posted
         */
        template <typename Controller>
        NetworkHandler(AppEventLoop &eventLoop, const std::string &name, Controller *controller, void (Controller::*function)(const net::Buffer &, net::Buffer &));
        
        /**
         *  @brief  Post the service content in the event loop. The received buffer
         *          from the service update is copied and pushed to the event queue
         *          using the AppEventLoop::postEvent() method.
         *          
         *  @param  buffer the received buffer from the service update
         */
        void postServiceContent(const net::Buffer &buffer);
        
        /**
         *  @brief  Send directly the service content. The received buffer
         *          from the service update is not copied but directly sent to 
         *          the user using the AppEventLoop::postEvent() method.
         *          
         *  @param  buffer the received buffer from the service update
         */
        void sendServiceContent(const net::Buffer &buffer);
        
        /**
         *  @brief  Send directly the request content. The received buffer
         *          from the request handler is not copied but directly sent to 
         *          the user using the AppEventLoop::postEvent() method.
         *          
         *  @param  request the received buffer from the request handler
         *  @param  response the buffer to send back as response
         */
        void sendRequestEvent(const net::Buffer &request, net::Buffer &response);
        
        /**
         *  @brief  Post the command content in the event loop. The received buffer
         *          from the command is copied and pushed to the event queue
         *          using the AppEventLoop::postEvent() method.
         *          
         *  @param  buffer the received buffer from the command handler
         */
        void postCommandEvent(const net::Buffer &buffer);
        
        /**
         *  @brief  Send directly the command content. The received buffer
         *          from the command handler is not copied but directly sent to 
         *          the user using the AppEventLoop::postEvent() method.
         *          
         *  @param  buffer the received buffer from the command handler
         */
        void sendCommandEvent(const net::Buffer &buffer);
        
      private:
        using ContentSignal = core::Signal<const net::Buffer&>;
        using RequestSignal = core::Signal<const net::Buffer&, net::Buffer&>;
        
        AppEventLoop           &m_eventLoop;
        const std::string       m_name = {""};
        const int               m_priority = {50};
        const int               m_maxNEvents = {std::numeric_limits<int>::max()};
        ContentSignal           m_sendContentSignal = {};
        RequestSignal           m_sendRequestSignal = {};
      };
      
      using NetworkHandlerPtr = std::shared_ptr<NetworkHandler>;
      using NetworkHandlerPtrMap = std::map<const std::string, NetworkHandlerPtr>;
      using ServerPtr = std::shared_ptr<net::Server>;
      using LoggerPtr = core::Logger::LoggerPtr;
      using LogLevel = core::Logger::Level;
      using Service = net::Service;
      using Client = net::Client;
      
    private:
      /// The application type
      std::string                  m_type = {""};
      /// The application name
      std::string                  m_name = {""};
      /// The application state
      std::string                  m_state = {"Unknown"};
      /// Whether the application is running
      bool                         m_running = {false};
      /// Whether the application is initialized
      bool                         m_initialized = {false};
      /// Whether the application statistics are available 
      bool                         m_statsEnabled = {true};
      /// The application statistics
      core::ProcessStats           m_stats = {};
      ///
      bool                         m_noServer = {false};
      /// The main server interface of the application
      ServerPtr                    m_server = {nullptr};
      /// The service for application state, updated when the state changes
      Service*                     m_pAppStateService = {nullptr};
      /// The main client interface of the application
      Client                       m_client = {};                     
      /// The map handling service updates from the client interface
      NetworkHandlerPtrMap         m_serviceHandlerPtrMap = {};
      /// The map handling request handlers from the server interface
      NetworkHandlerPtrMap         m_requestHandlerPtrMap = {};
      /// The map handling command handlers from the server interface
      NetworkHandlerPtrMap         m_commandHandlerPtrMap = {}; 
      /// The json value handling the application statistics
      core::json                   m_statistics = {};                 
      /// The application logger
      LoggerPtr                    m_logger = {nullptr};
      /// The logger log level
      LogLevel                     m_logLevel = {spdlog::level::info};
      ///
      AppTimer*                    m_appStatTimer = {nullptr};
      
    protected:
      /// The application event loop
      AppEventLoop                 m_eventLoop = {};
    };
    
    //-------------------------------------------------------------------------------------------------
    //-------------------------------------------------------------------------------------------------
    
    template <typename T>
    inline void Application::sendCommand(const std::string &cname, const T &contents, bool blocking) const {
      m_client.sendCommand(cname, contents, blocking);
    }
    
    //-------------------------------------------------------------------------------------------------
    
    template <typename Operation>
    inline void Application::sendRequest(const std::string &rname, const net::Buffer &request, Operation operation) {
      m_client.sendRequest(rname, request, operation);
    }
    
    //-------------------------------------------------------------------------------------------------
    
    template <typename Controller>
    inline Application::NetworkHandler::NetworkHandler(AppEventLoop &eventLoop, const std::string &sname, Controller *controller, void (Controller::*function)(const net::Buffer &buffer)) :
      m_eventLoop(eventLoop),
      m_name(sname),
      m_priority(0),
      m_maxNEvents(0) {
      m_sendContentSignal.connect(controller, function);
    }

    //-------------------------------------------------------------------------------------------------

    template <typename Controller>
    inline Application::NetworkHandler::NetworkHandler(AppEventLoop &eventLoop, const std::string &sname, Controller *controller, void (Controller::*function)(const net::Buffer &buffer, net::Buffer &response)) :
      m_eventLoop(eventLoop),
      m_name(sname),
      m_priority(0),
      m_maxNEvents(0) {
      m_sendRequestSignal.connect(controller, function);
    }
    
    //-------------------------------------------------------------------------------------------------
    
    template <typename Controller>
    inline void Application::directSubscribe(const std::string &serviceName, Controller *controller, void (Controller::*function)(const net::Buffer &)) {
      auto findIter = m_serviceHandlerPtrMap.find(serviceName);
      
      if(m_serviceHandlerPtrMap.end() != findIter) {
        dqm_error( "Application::directSubscribe(): couldn't subscribe twice to service '{0}'", serviceName );
        throw core::StatusCodeException(core::STATUS_CODE_ALREADY_PRESENT);
      }
      
      auto handler = std::make_shared<NetworkHandler>(m_eventLoop, serviceName, controller, function);
      m_serviceHandlerPtrMap.insert(NetworkHandlerPtrMap::value_type(serviceName, handler));
      m_client.subscribe(serviceName, handler.get(), &Application::NetworkHandler::sendServiceContent);
    }
    
    //-------------------------------------------------------------------------------------------------
    
    template <typename Controller>
    inline void Application::createRequestHandler(const std::string &requestName, Controller *controller, void (Controller::*function)(const net::Buffer &, net::Buffer &)) {
      if(not m_server) {
        dqm_error( "Application::createRequestHandler(): couldn't create request handler '{0}', server is not yet allocated", requestName );
        throw core::StatusCodeException(core::STATUS_CODE_NOT_INITIALIZED);
      }
      auto findIter = m_requestHandlerPtrMap.find(requestName);
      
      if(m_requestHandlerPtrMap.end() != findIter) {
        dqm_error( "Application::createRequestHandler(): couldn't create twice request handler '{0}'", requestName );
        throw core::StatusCodeException(core::STATUS_CODE_ALREADY_PRESENT);
      }
      
      auto handler = std::make_shared<NetworkHandler>(m_eventLoop, requestName, controller, function);
      m_serviceHandlerPtrMap.insert(NetworkHandlerPtrMap::value_type(requestName, handler));
      m_server->createRequestHandler(requestName, handler.get(), &Application::NetworkHandler::sendRequestEvent);      
    }
    
    //-------------------------------------------------------------------------------------------------
    
    template <typename Controller>
    inline void Application::createDirectCommand(const std::string &commandName, Controller *controller, void (Controller::*function)(const net::Buffer &)) {
      if(not m_server) {
        dqm_error( "Application::createDirectCommand(): couldn't create command handler '{0}', server is not yet allocated", commandName );
        throw core::StatusCodeException(core::STATUS_CODE_NOT_INITIALIZED);
      }
      
      auto findIter = m_commandHandlerPtrMap.find(commandName);
      
      if(m_commandHandlerPtrMap.end() != findIter) {
        dqm_error( "Application::createDirectCommand(): couldn't create command handler '{0}' twice", commandName );
        throw core::StatusCodeException(core::STATUS_CODE_ALREADY_PRESENT);
      }
      
      auto handler = std::make_shared<NetworkHandler>(m_eventLoop, commandName, controller, function);
      m_commandHandlerPtrMap.insert(NetworkHandlerPtrMap::value_type(commandName, handler));
      m_server->createCommandHandler(commandName, handler.get(), &Application::NetworkHandler::sendCommandEvent);
    }
    
  }

} 

#endif  //  DQM4HEP_APPLICATION_H
