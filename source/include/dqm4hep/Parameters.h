/// \file Parameters.h
/*
*
* Parameters.h header template automatically generated by a class generator
* Creation date : mer. janv. 25 2017
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


#ifndef PARAMETERS_H
#define PARAMETERS_H

#include "dqm4hep/Parameter.h"

namespace dqm4hep {

  namespace core {

    /**
     * Parameters class
     *
     * Interface to store and acces a set of parameters.
     * Internally stored as a set of key -> value pairs, parameters
     * can be accessed using the get() method. The string parameter
     * value is converted to the target type and wrapped in a
     * Parameter<t> object.
     */
    class Parameters
    {
    public:
      /**
       * Constructor
       */
      Parameters();

      /**
       * Destructor
       */
      ~Parameters();

      /**
       * Get all parameter names
       */
      StringVector getKeys() const;

      /**
       * Get parameter values as string
       */
      StringVector getValues() const;

      /**
       * Whether the target parameter exists
       *
       * @param  name the parameter name to lookup
       */
      bool exists(const std::string &name) const;

      /**
       * Get a parameter. Convert the parameter into target type
       * and wrap it in a Parameter<T>. If the parameter doesn't exists
       * the Parameter<T> default constructor is used.
       *
       * @param name the parameter name
       */
      template <typename T>
      Parameter<T> get(const std::string &name) const;

      /**
       * Get a parameter. Convert the parameter into target type
       * and wrap it in a Parameter<T>. If the parameter doesn't exists
       * the default value is used instead into the Parameter<t> constructor.
       *
       * @param name the parameter name
       */
      template <typename T>
      Parameter<T> get(const std::string &name, const T &defaultValue) const;

      /**
       * Set a parameter. Replace it if already exists.
       * The value is converted to std::string and store in
       * an internal map.
       */
      template <typename T>
      void set(const std::string &name, const T &value);

      /**
       * Remove all parameters
       */
      void reset();

    protected:
      ParameterMap                     m_parametersMap;     ///< The parameter map (string -> string)
    };

    //-------------------------------------------------------------------------------------------------
    //-------------------------------------------------------------------------------------------------

    template <typename T>
    inline Parameter<T> Parameters::get(const std::string &name) const
    {
      Parameter<T> parameter;
      auto findIter = m_parametersMap.find(name);

      if(findIter == m_parametersMap.end())
        return std::move(parameter);

      T value;

      if(!DQM4HEP::stringToType(findIter->second, value))
        return std::move(parameter);

      parameter = value;

      return std::move(parameter);
    }

    //-------------------------------------------------------------------------------------------------

    template <typename T>
    inline Parameter<T> Parameters::get(const std::string &name, const T &defaultValue) const
    {
      Parameter<T> parameter(defaultValue);
      auto findIter = m_parametersMap.find(name);

      if(findIter == m_parametersMap.end())
        return std::move(parameter);

      T value;

      if(!DQM4HEP::stringToType(findIter->second, value))
        return std::move(parameter);

      parameter = value;

      return std::move(parameter);
    }

    //-------------------------------------------------------------------------------------------------

    template <typename T>
    inline void Parameters::set(const std::string &name, const T &value)
    {
      auto findIter = m_parametersMap.find(name);

      if(findIter == m_parametersMap.end())
        findIter = m_parametersMap.insert(ParameterMap::value_type(name, "")).first;

      findIter->second = DQM4HEP::typeToString(value);
    }

  }

}

#endif  //  PARAMETERS_H
