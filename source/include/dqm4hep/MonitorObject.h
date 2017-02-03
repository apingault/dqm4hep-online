  /// \file MonitorObject.h
/*
 *
 * MonitorObject.h header template automatically generated by a class generator
 * Creation date : jeu. f�vr. 2 2017
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


#ifndef MONITOROBJECT_H
#define MONITOROBJECT_H

// -- dqm4hep headers
#include "dqm4hep/DQM4HEP.h"

// -- json headers
#include "json/json.h"

namespace dqm4hep {

  namespace core {

    /**
     * Color enum.
     * Same color enum as ROOT
     */
    enum Color
    {
      White   = 0,
      Black   = 1,
      Gray    = 920,
      Red     = 632,
      Green   = 416,
      Blue    = 600,
      Yellow  = 400,
      Magenta = 616,
      Cyan    = 432,
      Orange  = 800,
      Spring  = 820,
      Teal    = 840,
      Azure   = 860,
      Violet  = 880,
      Pink    = 900
    };

    /**
     * MarkerStyle enum
     * Same marker style enum as ROOT
     */
    enum MarkerStyle
    {
      Point = 7,
      FullCircle = 20,
      FullSquare = 21,
      FullTriangle = 22,
      FullDiamond = 33,
      FullCross = 34,
      FullStar = 29,
      Circle = 24,
      Square = 25,
      Triangle = 26,
      Diamond = 27,
      Cross = 28,
      Star = 30
    };

    /**
     * LineStyle enum
     * Same line style enum as ROOT
     */
    enum LineStyle
    {
      SolidLine,                  ///< solid line
      DashLine,                   ///< dash line
      DotLine,                    ///< dot line
      DashDotLine,                ///< alternate dashes and dots
      DashDotDotLine              ///< alternate dashes and double dots
    };

    /**
     * FillStyle enum
     */
    enum FillStyle
    {
      Transparent = 0,
      Solid
    };

    /**
     * Axis struct
     */
    struct Axis
    {
      Axis();

      std::string               m_title;
      float                     m_titleSize;
      Color                     m_titleColor;
      float                     m_labelSize;
      Color                     m_labelColor;
    };

    inline Axis::Axis() :
      m_titleSize(0.04),
      m_titleColor(Black),
      m_labelSize(0.04),
      m_labelColor(Black)
    {
      /* nop */
    }

    /**
     * @brief MonitorObject class
     */
    class MonitorObject
    {
    public:
     /**
      * @brief Ctor
      */
     MonitorObject();

     /**
      * @brief Dtor
      */
     virtual ~MonitorObject();

     /**
      * [setUseUpdateCache description]
      * @param updateCache [description]
      */
     void setUseUpdateCache(bool updateCache);

     /**
      * [useUpdateCache description]
      * @return [description]
      */
     bool useUpdateCache() const;

     /**
      * [fromJson description]
      * @param value [description]
      */
     virtual void fromJson(const Json::Value &value) = 0;

     /**
      * [toJson description]
      * @param value [description]
      * @param full  [description]
      */
     virtual void toJson(Json::Value &value, bool full = true) = 0;

    protected:
      bool                                           m_useUpdateCache;
    };

  }

}

#endif  //  MONITOROBJECT_H
