  /// \file JsonConfigurationIO.h
/*
 *
 * JsonConfigurationIO.h header template automatically generated by a class generator
 * Creation date : jeu. janv. 26 2017
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


#ifndef JSONCONFIGURATIONIO_H
#define JSONCONFIGURATIONIO_H

#include "dqm4hep/ConfigurationIO.h"

#include <json/json.h>

namespace dqm4hep {

  namespace core {

    class TiXmlElement;
    class ConfigurationHandle;

    /**
     * @brief JsonConfigurationIO class
     */
    class JsonConfigurationIO : public ConfigurationIO
    {
     public:
       /**
        *
        */
       ~JsonConfigurationIO() {}

       /**
        * Read settings from the json input file and store the read parameters into the parameter directory
        *
        * @param  jsonFileName the json input file
        * @param  pDirectory the top-level directory to store parameters
        */
       StatusCode read(const std::string &jsonFileName, ParameterDirectory *pDirectory);

       /**
        * Write settings from the directory into the output
        *
        * @param  jsonFileName the json output file where to store parameters
        * @param  pDirectory the top-level directory to pull parameters from
        */
       StatusCode write(const std::string &jsonFileName, ParameterDirectory *pDirectory);

       /**
        * Get the configuration IO type (json)
        */
       std::string getType() const;

     private:

       StatusCode read(const Json::Value &value, ParameterDirectory *pDirectory);

       StatusCode write(Json::Value &value, const ConfigurationHandle &configHandle);
    };

  }

}

#endif  //  JSONCONFIGURATIONIO_H
