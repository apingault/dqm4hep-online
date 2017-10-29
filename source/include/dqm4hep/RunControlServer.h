  /// \file RunControlServer.h
/*
 *
 * RunControlServer.h header template automatically generated by a class generator
 * Creation date : ven. oct. 27 2017
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
 * @copyright
 */


#ifndef DQM4HEP_RUNCONTROLSERVER_H
#define DQM4HEP_RUNCONTROLSERVER_H

#include <dqm4hep/Internal.h>
#include <dqm4hep/StatusCodes.h>
#include <dqm4hep/RunControl.h>
#include <dqm4hep/Server.h>

namespace dqm4hep {

  namespace online {

    /** RunControlServer class
     */
    class RunControlServer
    {
    public:
      /** Constructor
       */
      RunControlServer();

      /** Destructor
       */
      ~RunControlServer();

      /** Set the run control name
       *  Must be called before run()
       */
      void setName(const std::string &name);

      /**
       */
      void setPassword(const std::string &pwd);

      /** Set the plugin name of the ouside interface
       */
      void setInterface(const std::string &name);

      /** Run the server
       */
      void run();

      /** Stop the server
       */
      void stop();

    private:
      void sor(dqm4hep::core::Run &run);
      void eor(const dqm4hep::core::Run &run);
      void sendCurrentRun(const dqm4hep::net::Buffer &request, dqm4hep::net::Buffer &response);

    private:
      RunControl                    m_runControl;
      dqm4hep::net::Server         *m_pServer;
      dqm4hep::net::Service        *m_pSorService;
      dqm4hep::net::Service        *m_pEorService;
      bool                          m_stopFlag;
      std::string                   m_interfaceName;
    };

  }

}

#endif  //  DQM4HEP_RUNCONTROLSERVER_H