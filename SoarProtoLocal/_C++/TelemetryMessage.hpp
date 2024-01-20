/*
 *  Copyright (C) 2020-2023 Embedded AMS B.V. - All Rights Reserved
 *
 *  This file is part of Embedded Proto.
 *
 *  Embedded Proto is open source software: you can redistribute it and/or
 *  modify it under the terms of the GNU General Public License as published
 *  by the Free Software Foundation, version 3 of the license.
 *
 *  Embedded Proto  is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Embedded Proto. If not, see <https://www.gnu.org/licenses/>.
 *
 *  For commercial and closed source application please visit:
 *  <https://EmbeddedProto.com/license/>.
 *
 *  Embedded AMS B.V.
 *  Info:
 *    info at EmbeddedProto dot com
 *
 *  Postal address:
 *    Johan Huizingalaan 763a
 *    1066 VH, Amsterdam
 *    the Netherlands
 */

// This file is generated. Please do not edit!
#ifndef TELEMETRYMESSAGE_H
#define TELEMETRYMESSAGE_H

#include <cstdint>
#include <MessageInterface.h>
#include <WireFormatter.h>
#include <Fields.h>
#include <MessageSizeCalculator.h>
#include <ReadBufferSection.h>
#include <RepeatedFieldFixedSize.h>
#include <FieldStringBytes.h>
#include <Errors.h>
#include <Defines.h>
#include <limits>

// Include external proto definitions
#include <CoreProto.h>

namespace Proto {

class AltitudeType final: public ::EmbeddedProto::MessageInterface
{
  public:
    AltitudeType() = default;
    AltitudeType(const AltitudeType& rhs )
    {
      set_altitude(rhs.get_altitude());
      set_unit(rhs.get_unit());
    }

    AltitudeType(const AltitudeType&& rhs ) noexcept
    {
      set_altitude(rhs.get_altitude());
      set_unit(rhs.get_unit());
    }

    ~AltitudeType() override = default;

    enum class FieldNumber : uint32_t
    {
      NOT_SET = 0,
      ALTITUDE = 1,
      UNIT = 2
    };

    AltitudeType& operator=(const AltitudeType& rhs)
    {
      set_altitude(rhs.get_altitude());
      set_unit(rhs.get_unit());
      return *this;
    }

    AltitudeType& operator=(const AltitudeType&& rhs) noexcept
    {
      set_altitude(rhs.get_altitude());
      set_unit(rhs.get_unit());
      return *this;
    }

    static constexpr char const* ALTITUDE_NAME = "altitude";
    inline void clear_altitude() { altitude_.clear(); }
    inline void set_altitude(const int32_t& value) { altitude_ = value; }
    inline void set_altitude(const int32_t&& value) { altitude_ = value; }
    inline int32_t& mutable_altitude() { return altitude_.get(); }
    inline const int32_t& get_altitude() const { return altitude_.get(); }
    inline int32_t altitude() const { return altitude_.get(); }

    static constexpr char const* UNIT_NAME = "unit";
    inline void clear_unit() { unit_.clear(); }
    inline void set_unit(const int32_t& value) { unit_ = value; }
    inline void set_unit(const int32_t&& value) { unit_ = value; }
    inline int32_t& mutable_unit() { return unit_.get(); }
    inline const int32_t& get_unit() const { return unit_.get(); }
    inline int32_t unit() const { return unit_.get(); }


    ::EmbeddedProto::Error serialize(::EmbeddedProto::WriteBufferInterface& buffer) const override
    {
      ::EmbeddedProto::Error return_value = ::EmbeddedProto::Error::NO_ERRORS;

      if((0 != altitude_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = altitude_.serialize_with_id(static_cast<uint32_t>(FieldNumber::ALTITUDE), buffer, false);
      }

      if((0 != unit_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = unit_.serialize_with_id(static_cast<uint32_t>(FieldNumber::UNIT), buffer, false);
      }

      return return_value;
    };

    ::EmbeddedProto::Error deserialize(::EmbeddedProto::ReadBufferInterface& buffer) override
    {
      ::EmbeddedProto::Error return_value = ::EmbeddedProto::Error::NO_ERRORS;
      ::EmbeddedProto::WireFormatter::WireType wire_type = ::EmbeddedProto::WireFormatter::WireType::VARINT;
      uint32_t id_number = 0;
      FieldNumber id_tag = FieldNumber::NOT_SET;

      ::EmbeddedProto::Error tag_value = ::EmbeddedProto::WireFormatter::DeserializeTag(buffer, wire_type, id_number);
      while((::EmbeddedProto::Error::NO_ERRORS == return_value) && (::EmbeddedProto::Error::NO_ERRORS == tag_value))
      {
        id_tag = static_cast<FieldNumber>(id_number);
        switch(id_tag)
        {
          case FieldNumber::ALTITUDE:
            return_value = altitude_.deserialize_check_type(buffer, wire_type);
            break;

          case FieldNumber::UNIT:
            return_value = unit_.deserialize_check_type(buffer, wire_type);
            break;

          case FieldNumber::NOT_SET:
            return_value = ::EmbeddedProto::Error::INVALID_FIELD_ID;
            break;

          default:
            return_value = skip_unknown_field(buffer, wire_type);
            break;
        }

        if(::EmbeddedProto::Error::NO_ERRORS == return_value)
        {
          // Read the next tag.
          tag_value = ::EmbeddedProto::WireFormatter::DeserializeTag(buffer, wire_type, id_number);
        }
      }

      // When an error was detect while reading the tag but no other errors where found, set it in the return value.
      if((::EmbeddedProto::Error::NO_ERRORS == return_value)
         && (::EmbeddedProto::Error::NO_ERRORS != tag_value)
         && (::EmbeddedProto::Error::END_OF_BUFFER != tag_value)) // The end of the buffer is not an array in this case.
      {
        return_value = tag_value;
      }

      return return_value;
    };

    void clear() override
    {
      clear_altitude();
      clear_unit();

    }

    static char const* field_number_to_name(const FieldNumber fieldNumber)
    {
      char const* name = nullptr;
      switch(fieldNumber)
      {
        case FieldNumber::ALTITUDE:
          name = ALTITUDE_NAME;
          break;
        case FieldNumber::UNIT:
          name = UNIT_NAME;
          break;
        default:
          name = "Invalid FieldNumber";
          break;
      }
      return name;
    }

#ifdef MSG_TO_STRING

    ::EmbeddedProto::string_view to_string(::EmbeddedProto::string_view& str) const
    {
      return this->to_string(str, 0, nullptr, true);
    }

    ::EmbeddedProto::string_view to_string(::EmbeddedProto::string_view& str, const uint32_t indent_level, char const* name, const bool first_field) const override
    {
      ::EmbeddedProto::string_view left_chars = str;
      int32_t n_chars_used = 0;

      if(!first_field)
      {
        // Add a comma behind the previous field.
        n_chars_used = snprintf(left_chars.data, left_chars.size, ",\n");
        if(0 < n_chars_used)
        {
          // Update the character pointer and characters left in the array.
          left_chars.data += n_chars_used;
          left_chars.size -= n_chars_used;
        }
      }

      if(nullptr != name)
      {
        if( 0 == indent_level)
        {
          n_chars_used = snprintf(left_chars.data, left_chars.size, "\"%s\": {\n", name);
        }
        else
        {
          n_chars_used = snprintf(left_chars.data, left_chars.size, "%*s\"%s\": {\n", indent_level, " ", name);
        }
      }
      else
      {
        if( 0 == indent_level)
        {
          n_chars_used = snprintf(left_chars.data, left_chars.size, "{\n");
        }
        else
        {
          n_chars_used = snprintf(left_chars.data, left_chars.size, "%*s{\n", indent_level, " ");
        }
      }
      
      if(0 < n_chars_used)
      {
        left_chars.data += n_chars_used;
        left_chars.size -= n_chars_used;
      }

      left_chars = altitude_.to_string(left_chars, indent_level + 2, ALTITUDE_NAME, true);
      left_chars = unit_.to_string(left_chars, indent_level + 2, UNIT_NAME, false);
  
      if( 0 == indent_level) 
      {
        n_chars_used = snprintf(left_chars.data, left_chars.size, "\n}");
      }
      else 
      {
        n_chars_used = snprintf(left_chars.data, left_chars.size, "\n%*s}", indent_level, " ");
      }

      if(0 < n_chars_used)
      {
        left_chars.data += n_chars_used;
        left_chars.size -= n_chars_used;
      }

      return left_chars;
    }

#endif // End of MSG_TO_STRING

  private:


      EmbeddedProto::int32 altitude_ = 0;
      EmbeddedProto::int32 unit_ = 0;

};

class Baro final: public ::EmbeddedProto::MessageInterface
{
  public:
    Baro() = default;
    Baro(const Baro& rhs )
    {
      set_baro_pressure(rhs.get_baro_pressure());
      set_baro_temp(rhs.get_baro_temp());
    }

    Baro(const Baro&& rhs ) noexcept
    {
      set_baro_pressure(rhs.get_baro_pressure());
      set_baro_temp(rhs.get_baro_temp());
    }

    ~Baro() override = default;

    enum class FieldNumber : uint32_t
    {
      NOT_SET = 0,
      BARO_PRESSURE = 1,
      BARO_TEMP = 2
    };

    Baro& operator=(const Baro& rhs)
    {
      set_baro_pressure(rhs.get_baro_pressure());
      set_baro_temp(rhs.get_baro_temp());
      return *this;
    }

    Baro& operator=(const Baro&& rhs) noexcept
    {
      set_baro_pressure(rhs.get_baro_pressure());
      set_baro_temp(rhs.get_baro_temp());
      return *this;
    }

    static constexpr char const* BARO_PRESSURE_NAME = "baro_pressure";
    inline void clear_baro_pressure() { baro_pressure_.clear(); }
    inline void set_baro_pressure(const int32_t& value) { baro_pressure_ = value; }
    inline void set_baro_pressure(const int32_t&& value) { baro_pressure_ = value; }
    inline int32_t& mutable_baro_pressure() { return baro_pressure_.get(); }
    inline const int32_t& get_baro_pressure() const { return baro_pressure_.get(); }
    inline int32_t baro_pressure() const { return baro_pressure_.get(); }

    static constexpr char const* BARO_TEMP_NAME = "baro_temp";
    inline void clear_baro_temp() { baro_temp_.clear(); }
    inline void set_baro_temp(const int32_t& value) { baro_temp_ = value; }
    inline void set_baro_temp(const int32_t&& value) { baro_temp_ = value; }
    inline int32_t& mutable_baro_temp() { return baro_temp_.get(); }
    inline const int32_t& get_baro_temp() const { return baro_temp_.get(); }
    inline int32_t baro_temp() const { return baro_temp_.get(); }


    ::EmbeddedProto::Error serialize(::EmbeddedProto::WriteBufferInterface& buffer) const override
    {
      ::EmbeddedProto::Error return_value = ::EmbeddedProto::Error::NO_ERRORS;

      if((0 != baro_pressure_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = baro_pressure_.serialize_with_id(static_cast<uint32_t>(FieldNumber::BARO_PRESSURE), buffer, false);
      }

      if((0 != baro_temp_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = baro_temp_.serialize_with_id(static_cast<uint32_t>(FieldNumber::BARO_TEMP), buffer, false);
      }

      return return_value;
    };

    ::EmbeddedProto::Error deserialize(::EmbeddedProto::ReadBufferInterface& buffer) override
    {
      ::EmbeddedProto::Error return_value = ::EmbeddedProto::Error::NO_ERRORS;
      ::EmbeddedProto::WireFormatter::WireType wire_type = ::EmbeddedProto::WireFormatter::WireType::VARINT;
      uint32_t id_number = 0;
      FieldNumber id_tag = FieldNumber::NOT_SET;

      ::EmbeddedProto::Error tag_value = ::EmbeddedProto::WireFormatter::DeserializeTag(buffer, wire_type, id_number);
      while((::EmbeddedProto::Error::NO_ERRORS == return_value) && (::EmbeddedProto::Error::NO_ERRORS == tag_value))
      {
        id_tag = static_cast<FieldNumber>(id_number);
        switch(id_tag)
        {
          case FieldNumber::BARO_PRESSURE:
            return_value = baro_pressure_.deserialize_check_type(buffer, wire_type);
            break;

          case FieldNumber::BARO_TEMP:
            return_value = baro_temp_.deserialize_check_type(buffer, wire_type);
            break;

          case FieldNumber::NOT_SET:
            return_value = ::EmbeddedProto::Error::INVALID_FIELD_ID;
            break;

          default:
            return_value = skip_unknown_field(buffer, wire_type);
            break;
        }

        if(::EmbeddedProto::Error::NO_ERRORS == return_value)
        {
          // Read the next tag.
          tag_value = ::EmbeddedProto::WireFormatter::DeserializeTag(buffer, wire_type, id_number);
        }
      }

      // When an error was detect while reading the tag but no other errors where found, set it in the return value.
      if((::EmbeddedProto::Error::NO_ERRORS == return_value)
         && (::EmbeddedProto::Error::NO_ERRORS != tag_value)
         && (::EmbeddedProto::Error::END_OF_BUFFER != tag_value)) // The end of the buffer is not an array in this case.
      {
        return_value = tag_value;
      }

      return return_value;
    };

    void clear() override
    {
      clear_baro_pressure();
      clear_baro_temp();

    }

    static char const* field_number_to_name(const FieldNumber fieldNumber)
    {
      char const* name = nullptr;
      switch(fieldNumber)
      {
        case FieldNumber::BARO_PRESSURE:
          name = BARO_PRESSURE_NAME;
          break;
        case FieldNumber::BARO_TEMP:
          name = BARO_TEMP_NAME;
          break;
        default:
          name = "Invalid FieldNumber";
          break;
      }
      return name;
    }

#ifdef MSG_TO_STRING

    ::EmbeddedProto::string_view to_string(::EmbeddedProto::string_view& str) const
    {
      return this->to_string(str, 0, nullptr, true);
    }

    ::EmbeddedProto::string_view to_string(::EmbeddedProto::string_view& str, const uint32_t indent_level, char const* name, const bool first_field) const override
    {
      ::EmbeddedProto::string_view left_chars = str;
      int32_t n_chars_used = 0;

      if(!first_field)
      {
        // Add a comma behind the previous field.
        n_chars_used = snprintf(left_chars.data, left_chars.size, ",\n");
        if(0 < n_chars_used)
        {
          // Update the character pointer and characters left in the array.
          left_chars.data += n_chars_used;
          left_chars.size -= n_chars_used;
        }
      }

      if(nullptr != name)
      {
        if( 0 == indent_level)
        {
          n_chars_used = snprintf(left_chars.data, left_chars.size, "\"%s\": {\n", name);
        }
        else
        {
          n_chars_used = snprintf(left_chars.data, left_chars.size, "%*s\"%s\": {\n", indent_level, " ", name);
        }
      }
      else
      {
        if( 0 == indent_level)
        {
          n_chars_used = snprintf(left_chars.data, left_chars.size, "{\n");
        }
        else
        {
          n_chars_used = snprintf(left_chars.data, left_chars.size, "%*s{\n", indent_level, " ");
        }
      }
      
      if(0 < n_chars_used)
      {
        left_chars.data += n_chars_used;
        left_chars.size -= n_chars_used;
      }

      left_chars = baro_pressure_.to_string(left_chars, indent_level + 2, BARO_PRESSURE_NAME, true);
      left_chars = baro_temp_.to_string(left_chars, indent_level + 2, BARO_TEMP_NAME, false);
  
      if( 0 == indent_level) 
      {
        n_chars_used = snprintf(left_chars.data, left_chars.size, "\n}");
      }
      else 
      {
        n_chars_used = snprintf(left_chars.data, left_chars.size, "\n%*s}", indent_level, " ");
      }

      if(0 < n_chars_used)
      {
        left_chars.data += n_chars_used;
        left_chars.size -= n_chars_used;
      }

      return left_chars;
    }

#endif // End of MSG_TO_STRING

  private:


      EmbeddedProto::int32 baro_pressure_ = 0;
      EmbeddedProto::int32 baro_temp_ = 0;

};

class Battery final: public ::EmbeddedProto::MessageInterface
{
  public:
    Battery() = default;
    Battery(const Battery& rhs )
    {
      set_p_source(rhs.get_p_source());
      set_volt(rhs.get_volt());
    }

    Battery(const Battery&& rhs ) noexcept
    {
      set_p_source(rhs.get_p_source());
      set_volt(rhs.get_volt());
    }

    ~Battery() override = default;

    enum class power_source : uint32_t
    {
      INVALID = 0,
      GROUND = 1,
      ROCKET = 2
    };

    enum class FieldNumber : uint32_t
    {
      NOT_SET = 0,
      P_SOURCE = 1,
      VOLT = 2
    };

    Battery& operator=(const Battery& rhs)
    {
      set_p_source(rhs.get_p_source());
      set_volt(rhs.get_volt());
      return *this;
    }

    Battery& operator=(const Battery&& rhs) noexcept
    {
      set_p_source(rhs.get_p_source());
      set_volt(rhs.get_volt());
      return *this;
    }

    static constexpr char const* P_SOURCE_NAME = "p_source";
    inline void clear_p_source() { p_source_.clear(); }
    inline void set_p_source(const power_source& value) { p_source_ = value; }
    inline void set_p_source(const power_source&& value) { p_source_ = value; }
    inline const power_source& get_p_source() const { return p_source_.get(); }
    inline power_source p_source() const { return p_source_.get(); }

    static constexpr char const* VOLT_NAME = "volt";
    inline void clear_volt() { volt_.clear(); }
    inline void set_volt(const int32_t& value) { volt_ = value; }
    inline void set_volt(const int32_t&& value) { volt_ = value; }
    inline int32_t& mutable_volt() { return volt_.get(); }
    inline const int32_t& get_volt() const { return volt_.get(); }
    inline int32_t volt() const { return volt_.get(); }


    ::EmbeddedProto::Error serialize(::EmbeddedProto::WriteBufferInterface& buffer) const override
    {
      ::EmbeddedProto::Error return_value = ::EmbeddedProto::Error::NO_ERRORS;

      if((static_cast<power_source>(0) != p_source_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = p_source_.serialize_with_id(static_cast<uint32_t>(FieldNumber::P_SOURCE), buffer, false);
      }

      if((0 != volt_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = volt_.serialize_with_id(static_cast<uint32_t>(FieldNumber::VOLT), buffer, false);
      }

      return return_value;
    };

    ::EmbeddedProto::Error deserialize(::EmbeddedProto::ReadBufferInterface& buffer) override
    {
      ::EmbeddedProto::Error return_value = ::EmbeddedProto::Error::NO_ERRORS;
      ::EmbeddedProto::WireFormatter::WireType wire_type = ::EmbeddedProto::WireFormatter::WireType::VARINT;
      uint32_t id_number = 0;
      FieldNumber id_tag = FieldNumber::NOT_SET;

      ::EmbeddedProto::Error tag_value = ::EmbeddedProto::WireFormatter::DeserializeTag(buffer, wire_type, id_number);
      while((::EmbeddedProto::Error::NO_ERRORS == return_value) && (::EmbeddedProto::Error::NO_ERRORS == tag_value))
      {
        id_tag = static_cast<FieldNumber>(id_number);
        switch(id_tag)
        {
          case FieldNumber::P_SOURCE:
            return_value = p_source_.deserialize_check_type(buffer, wire_type);
            break;

          case FieldNumber::VOLT:
            return_value = volt_.deserialize_check_type(buffer, wire_type);
            break;

          case FieldNumber::NOT_SET:
            return_value = ::EmbeddedProto::Error::INVALID_FIELD_ID;
            break;

          default:
            return_value = skip_unknown_field(buffer, wire_type);
            break;
        }

        if(::EmbeddedProto::Error::NO_ERRORS == return_value)
        {
          // Read the next tag.
          tag_value = ::EmbeddedProto::WireFormatter::DeserializeTag(buffer, wire_type, id_number);
        }
      }

      // When an error was detect while reading the tag but no other errors where found, set it in the return value.
      if((::EmbeddedProto::Error::NO_ERRORS == return_value)
         && (::EmbeddedProto::Error::NO_ERRORS != tag_value)
         && (::EmbeddedProto::Error::END_OF_BUFFER != tag_value)) // The end of the buffer is not an array in this case.
      {
        return_value = tag_value;
      }

      return return_value;
    };

    void clear() override
    {
      clear_p_source();
      clear_volt();

    }

    static char const* field_number_to_name(const FieldNumber fieldNumber)
    {
      char const* name = nullptr;
      switch(fieldNumber)
      {
        case FieldNumber::P_SOURCE:
          name = P_SOURCE_NAME;
          break;
        case FieldNumber::VOLT:
          name = VOLT_NAME;
          break;
        default:
          name = "Invalid FieldNumber";
          break;
      }
      return name;
    }

#ifdef MSG_TO_STRING

    ::EmbeddedProto::string_view to_string(::EmbeddedProto::string_view& str) const
    {
      return this->to_string(str, 0, nullptr, true);
    }

    ::EmbeddedProto::string_view to_string(::EmbeddedProto::string_view& str, const uint32_t indent_level, char const* name, const bool first_field) const override
    {
      ::EmbeddedProto::string_view left_chars = str;
      int32_t n_chars_used = 0;

      if(!first_field)
      {
        // Add a comma behind the previous field.
        n_chars_used = snprintf(left_chars.data, left_chars.size, ",\n");
        if(0 < n_chars_used)
        {
          // Update the character pointer and characters left in the array.
          left_chars.data += n_chars_used;
          left_chars.size -= n_chars_used;
        }
      }

      if(nullptr != name)
      {
        if( 0 == indent_level)
        {
          n_chars_used = snprintf(left_chars.data, left_chars.size, "\"%s\": {\n", name);
        }
        else
        {
          n_chars_used = snprintf(left_chars.data, left_chars.size, "%*s\"%s\": {\n", indent_level, " ", name);
        }
      }
      else
      {
        if( 0 == indent_level)
        {
          n_chars_used = snprintf(left_chars.data, left_chars.size, "{\n");
        }
        else
        {
          n_chars_used = snprintf(left_chars.data, left_chars.size, "%*s{\n", indent_level, " ");
        }
      }
      
      if(0 < n_chars_used)
      {
        left_chars.data += n_chars_used;
        left_chars.size -= n_chars_used;
      }

      left_chars = p_source_.to_string(left_chars, indent_level + 2, P_SOURCE_NAME, true);
      left_chars = volt_.to_string(left_chars, indent_level + 2, VOLT_NAME, false);
  
      if( 0 == indent_level) 
      {
        n_chars_used = snprintf(left_chars.data, left_chars.size, "\n}");
      }
      else 
      {
        n_chars_used = snprintf(left_chars.data, left_chars.size, "\n%*s}", indent_level, " ");
      }

      if(0 < n_chars_used)
      {
        left_chars.data += n_chars_used;
        left_chars.size -= n_chars_used;
      }

      return left_chars;
    }

#endif // End of MSG_TO_STRING

  private:


      EmbeddedProto::enumeration<power_source> p_source_ = static_cast<power_source>(0);
      EmbeddedProto::int32 volt_ = 0;

};

class CombustionControlStatus final: public ::EmbeddedProto::MessageInterface
{
  public:
    CombustionControlStatus() = default;
    CombustionControlStatus(const CombustionControlStatus& rhs )
    {
      set_vent_open(rhs.get_vent_open());
      set_drain_open(rhs.get_drain_open());
      set_mev_power_enable(rhs.get_mev_power_enable());
    }

    CombustionControlStatus(const CombustionControlStatus&& rhs ) noexcept
    {
      set_vent_open(rhs.get_vent_open());
      set_drain_open(rhs.get_drain_open());
      set_mev_power_enable(rhs.get_mev_power_enable());
    }

    ~CombustionControlStatus() override = default;

    enum class FieldNumber : uint32_t
    {
      NOT_SET = 0,
      VENT_OPEN = 2,
      DRAIN_OPEN = 3,
      MEV_POWER_ENABLE = 4
    };

    CombustionControlStatus& operator=(const CombustionControlStatus& rhs)
    {
      set_vent_open(rhs.get_vent_open());
      set_drain_open(rhs.get_drain_open());
      set_mev_power_enable(rhs.get_mev_power_enable());
      return *this;
    }

    CombustionControlStatus& operator=(const CombustionControlStatus&& rhs) noexcept
    {
      set_vent_open(rhs.get_vent_open());
      set_drain_open(rhs.get_drain_open());
      set_mev_power_enable(rhs.get_mev_power_enable());
      return *this;
    }

    static constexpr char const* VENT_OPEN_NAME = "vent_open";
    inline void clear_vent_open() { vent_open_.clear(); }
    inline void set_vent_open(const bool& value) { vent_open_ = value; }
    inline void set_vent_open(const bool&& value) { vent_open_ = value; }
    inline bool& mutable_vent_open() { return vent_open_.get(); }
    inline const bool& get_vent_open() const { return vent_open_.get(); }
    inline bool vent_open() const { return vent_open_.get(); }

    static constexpr char const* DRAIN_OPEN_NAME = "drain_open";
    inline void clear_drain_open() { drain_open_.clear(); }
    inline void set_drain_open(const bool& value) { drain_open_ = value; }
    inline void set_drain_open(const bool&& value) { drain_open_ = value; }
    inline bool& mutable_drain_open() { return drain_open_.get(); }
    inline const bool& get_drain_open() const { return drain_open_.get(); }
    inline bool drain_open() const { return drain_open_.get(); }

    static constexpr char const* MEV_POWER_ENABLE_NAME = "mev_power_enable";
    inline void clear_mev_power_enable() { mev_power_enable_.clear(); }
    inline void set_mev_power_enable(const bool& value) { mev_power_enable_ = value; }
    inline void set_mev_power_enable(const bool&& value) { mev_power_enable_ = value; }
    inline bool& mutable_mev_power_enable() { return mev_power_enable_.get(); }
    inline const bool& get_mev_power_enable() const { return mev_power_enable_.get(); }
    inline bool mev_power_enable() const { return mev_power_enable_.get(); }


    ::EmbeddedProto::Error serialize(::EmbeddedProto::WriteBufferInterface& buffer) const override
    {
      ::EmbeddedProto::Error return_value = ::EmbeddedProto::Error::NO_ERRORS;

      if((false != vent_open_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = vent_open_.serialize_with_id(static_cast<uint32_t>(FieldNumber::VENT_OPEN), buffer, false);
      }

      if((false != drain_open_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = drain_open_.serialize_with_id(static_cast<uint32_t>(FieldNumber::DRAIN_OPEN), buffer, false);
      }

      if((false != mev_power_enable_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = mev_power_enable_.serialize_with_id(static_cast<uint32_t>(FieldNumber::MEV_POWER_ENABLE), buffer, false);
      }

      return return_value;
    };

    ::EmbeddedProto::Error deserialize(::EmbeddedProto::ReadBufferInterface& buffer) override
    {
      ::EmbeddedProto::Error return_value = ::EmbeddedProto::Error::NO_ERRORS;
      ::EmbeddedProto::WireFormatter::WireType wire_type = ::EmbeddedProto::WireFormatter::WireType::VARINT;
      uint32_t id_number = 0;
      FieldNumber id_tag = FieldNumber::NOT_SET;

      ::EmbeddedProto::Error tag_value = ::EmbeddedProto::WireFormatter::DeserializeTag(buffer, wire_type, id_number);
      while((::EmbeddedProto::Error::NO_ERRORS == return_value) && (::EmbeddedProto::Error::NO_ERRORS == tag_value))
      {
        id_tag = static_cast<FieldNumber>(id_number);
        switch(id_tag)
        {
          case FieldNumber::VENT_OPEN:
            return_value = vent_open_.deserialize_check_type(buffer, wire_type);
            break;

          case FieldNumber::DRAIN_OPEN:
            return_value = drain_open_.deserialize_check_type(buffer, wire_type);
            break;

          case FieldNumber::MEV_POWER_ENABLE:
            return_value = mev_power_enable_.deserialize_check_type(buffer, wire_type);
            break;

          case FieldNumber::NOT_SET:
            return_value = ::EmbeddedProto::Error::INVALID_FIELD_ID;
            break;

          default:
            return_value = skip_unknown_field(buffer, wire_type);
            break;
        }

        if(::EmbeddedProto::Error::NO_ERRORS == return_value)
        {
          // Read the next tag.
          tag_value = ::EmbeddedProto::WireFormatter::DeserializeTag(buffer, wire_type, id_number);
        }
      }

      // When an error was detect while reading the tag but no other errors where found, set it in the return value.
      if((::EmbeddedProto::Error::NO_ERRORS == return_value)
         && (::EmbeddedProto::Error::NO_ERRORS != tag_value)
         && (::EmbeddedProto::Error::END_OF_BUFFER != tag_value)) // The end of the buffer is not an array in this case.
      {
        return_value = tag_value;
      }

      return return_value;
    };

    void clear() override
    {
      clear_vent_open();
      clear_drain_open();
      clear_mev_power_enable();

    }

    static char const* field_number_to_name(const FieldNumber fieldNumber)
    {
      char const* name = nullptr;
      switch(fieldNumber)
      {
        case FieldNumber::VENT_OPEN:
          name = VENT_OPEN_NAME;
          break;
        case FieldNumber::DRAIN_OPEN:
          name = DRAIN_OPEN_NAME;
          break;
        case FieldNumber::MEV_POWER_ENABLE:
          name = MEV_POWER_ENABLE_NAME;
          break;
        default:
          name = "Invalid FieldNumber";
          break;
      }
      return name;
    }

#ifdef MSG_TO_STRING

    ::EmbeddedProto::string_view to_string(::EmbeddedProto::string_view& str) const
    {
      return this->to_string(str, 0, nullptr, true);
    }

    ::EmbeddedProto::string_view to_string(::EmbeddedProto::string_view& str, const uint32_t indent_level, char const* name, const bool first_field) const override
    {
      ::EmbeddedProto::string_view left_chars = str;
      int32_t n_chars_used = 0;

      if(!first_field)
      {
        // Add a comma behind the previous field.
        n_chars_used = snprintf(left_chars.data, left_chars.size, ",\n");
        if(0 < n_chars_used)
        {
          // Update the character pointer and characters left in the array.
          left_chars.data += n_chars_used;
          left_chars.size -= n_chars_used;
        }
      }

      if(nullptr != name)
      {
        if( 0 == indent_level)
        {
          n_chars_used = snprintf(left_chars.data, left_chars.size, "\"%s\": {\n", name);
        }
        else
        {
          n_chars_used = snprintf(left_chars.data, left_chars.size, "%*s\"%s\": {\n", indent_level, " ", name);
        }
      }
      else
      {
        if( 0 == indent_level)
        {
          n_chars_used = snprintf(left_chars.data, left_chars.size, "{\n");
        }
        else
        {
          n_chars_used = snprintf(left_chars.data, left_chars.size, "%*s{\n", indent_level, " ");
        }
      }
      
      if(0 < n_chars_used)
      {
        left_chars.data += n_chars_used;
        left_chars.size -= n_chars_used;
      }

      left_chars = vent_open_.to_string(left_chars, indent_level + 2, VENT_OPEN_NAME, true);
      left_chars = drain_open_.to_string(left_chars, indent_level + 2, DRAIN_OPEN_NAME, false);
      left_chars = mev_power_enable_.to_string(left_chars, indent_level + 2, MEV_POWER_ENABLE_NAME, false);
  
      if( 0 == indent_level) 
      {
        n_chars_used = snprintf(left_chars.data, left_chars.size, "\n}");
      }
      else 
      {
        n_chars_used = snprintf(left_chars.data, left_chars.size, "\n%*s}", indent_level, " ");
      }

      if(0 < n_chars_used)
      {
        left_chars.data += n_chars_used;
        left_chars.size -= n_chars_used;
      }

      return left_chars;
    }

#endif // End of MSG_TO_STRING

  private:


      EmbeddedProto::boolean vent_open_ = false;
      EmbeddedProto::boolean drain_open_ = false;
      EmbeddedProto::boolean mev_power_enable_ = false;

};

class DMBPressure final: public ::EmbeddedProto::MessageInterface
{
  public:
    DMBPressure() = default;
    DMBPressure(const DMBPressure& rhs )
    {
      set_upper_pv_pressure(rhs.get_upper_pv_pressure());
    }

    DMBPressure(const DMBPressure&& rhs ) noexcept
    {
      set_upper_pv_pressure(rhs.get_upper_pv_pressure());
    }

    ~DMBPressure() override = default;

    enum class FieldNumber : uint32_t
    {
      NOT_SET = 0,
      UPPER_PV_PRESSURE = 1
    };

    DMBPressure& operator=(const DMBPressure& rhs)
    {
      set_upper_pv_pressure(rhs.get_upper_pv_pressure());
      return *this;
    }

    DMBPressure& operator=(const DMBPressure&& rhs) noexcept
    {
      set_upper_pv_pressure(rhs.get_upper_pv_pressure());
      return *this;
    }

    static constexpr char const* UPPER_PV_PRESSURE_NAME = "upper_pv_pressure";
    inline void clear_upper_pv_pressure() { upper_pv_pressure_.clear(); }
    inline void set_upper_pv_pressure(const int32_t& value) { upper_pv_pressure_ = value; }
    inline void set_upper_pv_pressure(const int32_t&& value) { upper_pv_pressure_ = value; }
    inline int32_t& mutable_upper_pv_pressure() { return upper_pv_pressure_.get(); }
    inline const int32_t& get_upper_pv_pressure() const { return upper_pv_pressure_.get(); }
    inline int32_t upper_pv_pressure() const { return upper_pv_pressure_.get(); }


    ::EmbeddedProto::Error serialize(::EmbeddedProto::WriteBufferInterface& buffer) const override
    {
      ::EmbeddedProto::Error return_value = ::EmbeddedProto::Error::NO_ERRORS;

      if((0 != upper_pv_pressure_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = upper_pv_pressure_.serialize_with_id(static_cast<uint32_t>(FieldNumber::UPPER_PV_PRESSURE), buffer, false);
      }

      return return_value;
    };

    ::EmbeddedProto::Error deserialize(::EmbeddedProto::ReadBufferInterface& buffer) override
    {
      ::EmbeddedProto::Error return_value = ::EmbeddedProto::Error::NO_ERRORS;
      ::EmbeddedProto::WireFormatter::WireType wire_type = ::EmbeddedProto::WireFormatter::WireType::VARINT;
      uint32_t id_number = 0;
      FieldNumber id_tag = FieldNumber::NOT_SET;

      ::EmbeddedProto::Error tag_value = ::EmbeddedProto::WireFormatter::DeserializeTag(buffer, wire_type, id_number);
      while((::EmbeddedProto::Error::NO_ERRORS == return_value) && (::EmbeddedProto::Error::NO_ERRORS == tag_value))
      {
        id_tag = static_cast<FieldNumber>(id_number);
        switch(id_tag)
        {
          case FieldNumber::UPPER_PV_PRESSURE:
            return_value = upper_pv_pressure_.deserialize_check_type(buffer, wire_type);
            break;

          case FieldNumber::NOT_SET:
            return_value = ::EmbeddedProto::Error::INVALID_FIELD_ID;
            break;

          default:
            return_value = skip_unknown_field(buffer, wire_type);
            break;
        }

        if(::EmbeddedProto::Error::NO_ERRORS == return_value)
        {
          // Read the next tag.
          tag_value = ::EmbeddedProto::WireFormatter::DeserializeTag(buffer, wire_type, id_number);
        }
      }

      // When an error was detect while reading the tag but no other errors where found, set it in the return value.
      if((::EmbeddedProto::Error::NO_ERRORS == return_value)
         && (::EmbeddedProto::Error::NO_ERRORS != tag_value)
         && (::EmbeddedProto::Error::END_OF_BUFFER != tag_value)) // The end of the buffer is not an array in this case.
      {
        return_value = tag_value;
      }

      return return_value;
    };

    void clear() override
    {
      clear_upper_pv_pressure();

    }

    static char const* field_number_to_name(const FieldNumber fieldNumber)
    {
      char const* name = nullptr;
      switch(fieldNumber)
      {
        case FieldNumber::UPPER_PV_PRESSURE:
          name = UPPER_PV_PRESSURE_NAME;
          break;
        default:
          name = "Invalid FieldNumber";
          break;
      }
      return name;
    }

#ifdef MSG_TO_STRING

    ::EmbeddedProto::string_view to_string(::EmbeddedProto::string_view& str) const
    {
      return this->to_string(str, 0, nullptr, true);
    }

    ::EmbeddedProto::string_view to_string(::EmbeddedProto::string_view& str, const uint32_t indent_level, char const* name, const bool first_field) const override
    {
      ::EmbeddedProto::string_view left_chars = str;
      int32_t n_chars_used = 0;

      if(!first_field)
      {
        // Add a comma behind the previous field.
        n_chars_used = snprintf(left_chars.data, left_chars.size, ",\n");
        if(0 < n_chars_used)
        {
          // Update the character pointer and characters left in the array.
          left_chars.data += n_chars_used;
          left_chars.size -= n_chars_used;
        }
      }

      if(nullptr != name)
      {
        if( 0 == indent_level)
        {
          n_chars_used = snprintf(left_chars.data, left_chars.size, "\"%s\": {\n", name);
        }
        else
        {
          n_chars_used = snprintf(left_chars.data, left_chars.size, "%*s\"%s\": {\n", indent_level, " ", name);
        }
      }
      else
      {
        if( 0 == indent_level)
        {
          n_chars_used = snprintf(left_chars.data, left_chars.size, "{\n");
        }
        else
        {
          n_chars_used = snprintf(left_chars.data, left_chars.size, "%*s{\n", indent_level, " ");
        }
      }
      
      if(0 < n_chars_used)
      {
        left_chars.data += n_chars_used;
        left_chars.size -= n_chars_used;
      }

      left_chars = upper_pv_pressure_.to_string(left_chars, indent_level + 2, UPPER_PV_PRESSURE_NAME, true);
  
      if( 0 == indent_level) 
      {
        n_chars_used = snprintf(left_chars.data, left_chars.size, "\n}");
      }
      else 
      {
        n_chars_used = snprintf(left_chars.data, left_chars.size, "\n%*s}", indent_level, " ");
      }

      if(0 < n_chars_used)
      {
        left_chars.data += n_chars_used;
        left_chars.size -= n_chars_used;
      }

      return left_chars;
    }

#endif // End of MSG_TO_STRING

  private:


      EmbeddedProto::int32 upper_pv_pressure_ = 0;

};

class Flash final: public ::EmbeddedProto::MessageInterface
{
  public:
    Flash() = default;
    Flash(const Flash& rhs )
    {
      set_sector_address(rhs.get_sector_address());
      set_logging_rate(rhs.get_logging_rate());
    }

    Flash(const Flash&& rhs ) noexcept
    {
      set_sector_address(rhs.get_sector_address());
      set_logging_rate(rhs.get_logging_rate());
    }

    ~Flash() override = default;

    enum class FieldNumber : uint32_t
    {
      NOT_SET = 0,
      SECTOR_ADDRESS = 1,
      LOGGING_RATE = 2
    };

    Flash& operator=(const Flash& rhs)
    {
      set_sector_address(rhs.get_sector_address());
      set_logging_rate(rhs.get_logging_rate());
      return *this;
    }

    Flash& operator=(const Flash&& rhs) noexcept
    {
      set_sector_address(rhs.get_sector_address());
      set_logging_rate(rhs.get_logging_rate());
      return *this;
    }

    static constexpr char const* SECTOR_ADDRESS_NAME = "sector_address";
    inline void clear_sector_address() { sector_address_.clear(); }
    inline void set_sector_address(const uint32_t& value) { sector_address_ = value; }
    inline void set_sector_address(const uint32_t&& value) { sector_address_ = value; }
    inline uint32_t& mutable_sector_address() { return sector_address_.get(); }
    inline const uint32_t& get_sector_address() const { return sector_address_.get(); }
    inline uint32_t sector_address() const { return sector_address_.get(); }

    static constexpr char const* LOGGING_RATE_NAME = "logging_rate";
    inline void clear_logging_rate() { logging_rate_.clear(); }
    inline void set_logging_rate(const uint32_t& value) { logging_rate_ = value; }
    inline void set_logging_rate(const uint32_t&& value) { logging_rate_ = value; }
    inline uint32_t& mutable_logging_rate() { return logging_rate_.get(); }
    inline const uint32_t& get_logging_rate() const { return logging_rate_.get(); }
    inline uint32_t logging_rate() const { return logging_rate_.get(); }


    ::EmbeddedProto::Error serialize(::EmbeddedProto::WriteBufferInterface& buffer) const override
    {
      ::EmbeddedProto::Error return_value = ::EmbeddedProto::Error::NO_ERRORS;

      if((0U != sector_address_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = sector_address_.serialize_with_id(static_cast<uint32_t>(FieldNumber::SECTOR_ADDRESS), buffer, false);
      }

      if((0U != logging_rate_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = logging_rate_.serialize_with_id(static_cast<uint32_t>(FieldNumber::LOGGING_RATE), buffer, false);
      }

      return return_value;
    };

    ::EmbeddedProto::Error deserialize(::EmbeddedProto::ReadBufferInterface& buffer) override
    {
      ::EmbeddedProto::Error return_value = ::EmbeddedProto::Error::NO_ERRORS;
      ::EmbeddedProto::WireFormatter::WireType wire_type = ::EmbeddedProto::WireFormatter::WireType::VARINT;
      uint32_t id_number = 0;
      FieldNumber id_tag = FieldNumber::NOT_SET;

      ::EmbeddedProto::Error tag_value = ::EmbeddedProto::WireFormatter::DeserializeTag(buffer, wire_type, id_number);
      while((::EmbeddedProto::Error::NO_ERRORS == return_value) && (::EmbeddedProto::Error::NO_ERRORS == tag_value))
      {
        id_tag = static_cast<FieldNumber>(id_number);
        switch(id_tag)
        {
          case FieldNumber::SECTOR_ADDRESS:
            return_value = sector_address_.deserialize_check_type(buffer, wire_type);
            break;

          case FieldNumber::LOGGING_RATE:
            return_value = logging_rate_.deserialize_check_type(buffer, wire_type);
            break;

          case FieldNumber::NOT_SET:
            return_value = ::EmbeddedProto::Error::INVALID_FIELD_ID;
            break;

          default:
            return_value = skip_unknown_field(buffer, wire_type);
            break;
        }

        if(::EmbeddedProto::Error::NO_ERRORS == return_value)
        {
          // Read the next tag.
          tag_value = ::EmbeddedProto::WireFormatter::DeserializeTag(buffer, wire_type, id_number);
        }
      }

      // When an error was detect while reading the tag but no other errors where found, set it in the return value.
      if((::EmbeddedProto::Error::NO_ERRORS == return_value)
         && (::EmbeddedProto::Error::NO_ERRORS != tag_value)
         && (::EmbeddedProto::Error::END_OF_BUFFER != tag_value)) // The end of the buffer is not an array in this case.
      {
        return_value = tag_value;
      }

      return return_value;
    };

    void clear() override
    {
      clear_sector_address();
      clear_logging_rate();

    }

    static char const* field_number_to_name(const FieldNumber fieldNumber)
    {
      char const* name = nullptr;
      switch(fieldNumber)
      {
        case FieldNumber::SECTOR_ADDRESS:
          name = SECTOR_ADDRESS_NAME;
          break;
        case FieldNumber::LOGGING_RATE:
          name = LOGGING_RATE_NAME;
          break;
        default:
          name = "Invalid FieldNumber";
          break;
      }
      return name;
    }

#ifdef MSG_TO_STRING

    ::EmbeddedProto::string_view to_string(::EmbeddedProto::string_view& str) const
    {
      return this->to_string(str, 0, nullptr, true);
    }

    ::EmbeddedProto::string_view to_string(::EmbeddedProto::string_view& str, const uint32_t indent_level, char const* name, const bool first_field) const override
    {
      ::EmbeddedProto::string_view left_chars = str;
      int32_t n_chars_used = 0;

      if(!first_field)
      {
        // Add a comma behind the previous field.
        n_chars_used = snprintf(left_chars.data, left_chars.size, ",\n");
        if(0 < n_chars_used)
        {
          // Update the character pointer and characters left in the array.
          left_chars.data += n_chars_used;
          left_chars.size -= n_chars_used;
        }
      }

      if(nullptr != name)
      {
        if( 0 == indent_level)
        {
          n_chars_used = snprintf(left_chars.data, left_chars.size, "\"%s\": {\n", name);
        }
        else
        {
          n_chars_used = snprintf(left_chars.data, left_chars.size, "%*s\"%s\": {\n", indent_level, " ", name);
        }
      }
      else
      {
        if( 0 == indent_level)
        {
          n_chars_used = snprintf(left_chars.data, left_chars.size, "{\n");
        }
        else
        {
          n_chars_used = snprintf(left_chars.data, left_chars.size, "%*s{\n", indent_level, " ");
        }
      }
      
      if(0 < n_chars_used)
      {
        left_chars.data += n_chars_used;
        left_chars.size -= n_chars_used;
      }

      left_chars = sector_address_.to_string(left_chars, indent_level + 2, SECTOR_ADDRESS_NAME, true);
      left_chars = logging_rate_.to_string(left_chars, indent_level + 2, LOGGING_RATE_NAME, false);
  
      if( 0 == indent_level) 
      {
        n_chars_used = snprintf(left_chars.data, left_chars.size, "\n}");
      }
      else 
      {
        n_chars_used = snprintf(left_chars.data, left_chars.size, "\n%*s}", indent_level, " ");
      }

      if(0 < n_chars_used)
      {
        left_chars.data += n_chars_used;
        left_chars.size -= n_chars_used;
      }

      return left_chars;
    }

#endif // End of MSG_TO_STRING

  private:


      EmbeddedProto::uint32 sector_address_ = 0U;
      EmbeddedProto::uint32 logging_rate_ = 0U;

};

class IMU final: public ::EmbeddedProto::MessageInterface
{
  public:
    IMU() = default;
    IMU(const IMU& rhs )
    {
      set_accelx(rhs.get_accelx());
      set_accely(rhs.get_accely());
      set_accelz(rhs.get_accelz());
      set_gyrox(rhs.get_gyrox());
      set_gyroy(rhs.get_gyroy());
      set_gyroz(rhs.get_gyroz());
      set_magx(rhs.get_magx());
      set_magy(rhs.get_magy());
      set_magz(rhs.get_magz());
    }

    IMU(const IMU&& rhs ) noexcept
    {
      set_accelx(rhs.get_accelx());
      set_accely(rhs.get_accely());
      set_accelz(rhs.get_accelz());
      set_gyrox(rhs.get_gyrox());
      set_gyroy(rhs.get_gyroy());
      set_gyroz(rhs.get_gyroz());
      set_magx(rhs.get_magx());
      set_magy(rhs.get_magy());
      set_magz(rhs.get_magz());
    }

    ~IMU() override = default;

    enum class FieldNumber : uint32_t
    {
      NOT_SET = 0,
      ACCELX = 1,
      ACCELY = 2,
      ACCELZ = 3,
      GYROX = 4,
      GYROY = 5,
      GYROZ = 6,
      MAGX = 7,
      MAGY = 8,
      MAGZ = 9
    };

    IMU& operator=(const IMU& rhs)
    {
      set_accelx(rhs.get_accelx());
      set_accely(rhs.get_accely());
      set_accelz(rhs.get_accelz());
      set_gyrox(rhs.get_gyrox());
      set_gyroy(rhs.get_gyroy());
      set_gyroz(rhs.get_gyroz());
      set_magx(rhs.get_magx());
      set_magy(rhs.get_magy());
      set_magz(rhs.get_magz());
      return *this;
    }

    IMU& operator=(const IMU&& rhs) noexcept
    {
      set_accelx(rhs.get_accelx());
      set_accely(rhs.get_accely());
      set_accelz(rhs.get_accelz());
      set_gyrox(rhs.get_gyrox());
      set_gyroy(rhs.get_gyroy());
      set_gyroz(rhs.get_gyroz());
      set_magx(rhs.get_magx());
      set_magy(rhs.get_magy());
      set_magz(rhs.get_magz());
      return *this;
    }

    static constexpr char const* ACCELX_NAME = "accelx";
    inline void clear_accelx() { accelx_.clear(); }
    inline void set_accelx(const int32_t& value) { accelx_ = value; }
    inline void set_accelx(const int32_t&& value) { accelx_ = value; }
    inline int32_t& mutable_accelx() { return accelx_.get(); }
    inline const int32_t& get_accelx() const { return accelx_.get(); }
    inline int32_t accelx() const { return accelx_.get(); }

    static constexpr char const* ACCELY_NAME = "accely";
    inline void clear_accely() { accely_.clear(); }
    inline void set_accely(const int32_t& value) { accely_ = value; }
    inline void set_accely(const int32_t&& value) { accely_ = value; }
    inline int32_t& mutable_accely() { return accely_.get(); }
    inline const int32_t& get_accely() const { return accely_.get(); }
    inline int32_t accely() const { return accely_.get(); }

    static constexpr char const* ACCELZ_NAME = "accelz";
    inline void clear_accelz() { accelz_.clear(); }
    inline void set_accelz(const int32_t& value) { accelz_ = value; }
    inline void set_accelz(const int32_t&& value) { accelz_ = value; }
    inline int32_t& mutable_accelz() { return accelz_.get(); }
    inline const int32_t& get_accelz() const { return accelz_.get(); }
    inline int32_t accelz() const { return accelz_.get(); }

    static constexpr char const* GYROX_NAME = "gyrox";
    inline void clear_gyrox() { gyrox_.clear(); }
    inline void set_gyrox(const int32_t& value) { gyrox_ = value; }
    inline void set_gyrox(const int32_t&& value) { gyrox_ = value; }
    inline int32_t& mutable_gyrox() { return gyrox_.get(); }
    inline const int32_t& get_gyrox() const { return gyrox_.get(); }
    inline int32_t gyrox() const { return gyrox_.get(); }

    static constexpr char const* GYROY_NAME = "gyroy";
    inline void clear_gyroy() { gyroy_.clear(); }
    inline void set_gyroy(const int32_t& value) { gyroy_ = value; }
    inline void set_gyroy(const int32_t&& value) { gyroy_ = value; }
    inline int32_t& mutable_gyroy() { return gyroy_.get(); }
    inline const int32_t& get_gyroy() const { return gyroy_.get(); }
    inline int32_t gyroy() const { return gyroy_.get(); }

    static constexpr char const* GYROZ_NAME = "gyroz";
    inline void clear_gyroz() { gyroz_.clear(); }
    inline void set_gyroz(const int32_t& value) { gyroz_ = value; }
    inline void set_gyroz(const int32_t&& value) { gyroz_ = value; }
    inline int32_t& mutable_gyroz() { return gyroz_.get(); }
    inline const int32_t& get_gyroz() const { return gyroz_.get(); }
    inline int32_t gyroz() const { return gyroz_.get(); }

    static constexpr char const* MAGX_NAME = "magx";
    inline void clear_magx() { magx_.clear(); }
    inline void set_magx(const int32_t& value) { magx_ = value; }
    inline void set_magx(const int32_t&& value) { magx_ = value; }
    inline int32_t& mutable_magx() { return magx_.get(); }
    inline const int32_t& get_magx() const { return magx_.get(); }
    inline int32_t magx() const { return magx_.get(); }

    static constexpr char const* MAGY_NAME = "magy";
    inline void clear_magy() { magy_.clear(); }
    inline void set_magy(const int32_t& value) { magy_ = value; }
    inline void set_magy(const int32_t&& value) { magy_ = value; }
    inline int32_t& mutable_magy() { return magy_.get(); }
    inline const int32_t& get_magy() const { return magy_.get(); }
    inline int32_t magy() const { return magy_.get(); }

    static constexpr char const* MAGZ_NAME = "magz";
    inline void clear_magz() { magz_.clear(); }
    inline void set_magz(const int32_t& value) { magz_ = value; }
    inline void set_magz(const int32_t&& value) { magz_ = value; }
    inline int32_t& mutable_magz() { return magz_.get(); }
    inline const int32_t& get_magz() const { return magz_.get(); }
    inline int32_t magz() const { return magz_.get(); }


    ::EmbeddedProto::Error serialize(::EmbeddedProto::WriteBufferInterface& buffer) const override
    {
      ::EmbeddedProto::Error return_value = ::EmbeddedProto::Error::NO_ERRORS;

      if((0 != accelx_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = accelx_.serialize_with_id(static_cast<uint32_t>(FieldNumber::ACCELX), buffer, false);
      }

      if((0 != accely_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = accely_.serialize_with_id(static_cast<uint32_t>(FieldNumber::ACCELY), buffer, false);
      }

      if((0 != accelz_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = accelz_.serialize_with_id(static_cast<uint32_t>(FieldNumber::ACCELZ), buffer, false);
      }

      if((0 != gyrox_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = gyrox_.serialize_with_id(static_cast<uint32_t>(FieldNumber::GYROX), buffer, false);
      }

      if((0 != gyroy_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = gyroy_.serialize_with_id(static_cast<uint32_t>(FieldNumber::GYROY), buffer, false);
      }

      if((0 != gyroz_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = gyroz_.serialize_with_id(static_cast<uint32_t>(FieldNumber::GYROZ), buffer, false);
      }

      if((0 != magx_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = magx_.serialize_with_id(static_cast<uint32_t>(FieldNumber::MAGX), buffer, false);
      }

      if((0 != magy_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = magy_.serialize_with_id(static_cast<uint32_t>(FieldNumber::MAGY), buffer, false);
      }

      if((0 != magz_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = magz_.serialize_with_id(static_cast<uint32_t>(FieldNumber::MAGZ), buffer, false);
      }

      return return_value;
    };

    ::EmbeddedProto::Error deserialize(::EmbeddedProto::ReadBufferInterface& buffer) override
    {
      ::EmbeddedProto::Error return_value = ::EmbeddedProto::Error::NO_ERRORS;
      ::EmbeddedProto::WireFormatter::WireType wire_type = ::EmbeddedProto::WireFormatter::WireType::VARINT;
      uint32_t id_number = 0;
      FieldNumber id_tag = FieldNumber::NOT_SET;

      ::EmbeddedProto::Error tag_value = ::EmbeddedProto::WireFormatter::DeserializeTag(buffer, wire_type, id_number);
      while((::EmbeddedProto::Error::NO_ERRORS == return_value) && (::EmbeddedProto::Error::NO_ERRORS == tag_value))
      {
        id_tag = static_cast<FieldNumber>(id_number);
        switch(id_tag)
        {
          case FieldNumber::ACCELX:
            return_value = accelx_.deserialize_check_type(buffer, wire_type);
            break;

          case FieldNumber::ACCELY:
            return_value = accely_.deserialize_check_type(buffer, wire_type);
            break;

          case FieldNumber::ACCELZ:
            return_value = accelz_.deserialize_check_type(buffer, wire_type);
            break;

          case FieldNumber::GYROX:
            return_value = gyrox_.deserialize_check_type(buffer, wire_type);
            break;

          case FieldNumber::GYROY:
            return_value = gyroy_.deserialize_check_type(buffer, wire_type);
            break;

          case FieldNumber::GYROZ:
            return_value = gyroz_.deserialize_check_type(buffer, wire_type);
            break;

          case FieldNumber::MAGX:
            return_value = magx_.deserialize_check_type(buffer, wire_type);
            break;

          case FieldNumber::MAGY:
            return_value = magy_.deserialize_check_type(buffer, wire_type);
            break;

          case FieldNumber::MAGZ:
            return_value = magz_.deserialize_check_type(buffer, wire_type);
            break;

          case FieldNumber::NOT_SET:
            return_value = ::EmbeddedProto::Error::INVALID_FIELD_ID;
            break;

          default:
            return_value = skip_unknown_field(buffer, wire_type);
            break;
        }

        if(::EmbeddedProto::Error::NO_ERRORS == return_value)
        {
          // Read the next tag.
          tag_value = ::EmbeddedProto::WireFormatter::DeserializeTag(buffer, wire_type, id_number);
        }
      }

      // When an error was detect while reading the tag but no other errors where found, set it in the return value.
      if((::EmbeddedProto::Error::NO_ERRORS == return_value)
         && (::EmbeddedProto::Error::NO_ERRORS != tag_value)
         && (::EmbeddedProto::Error::END_OF_BUFFER != tag_value)) // The end of the buffer is not an array in this case.
      {
        return_value = tag_value;
      }

      return return_value;
    };

    void clear() override
    {
      clear_accelx();
      clear_accely();
      clear_accelz();
      clear_gyrox();
      clear_gyroy();
      clear_gyroz();
      clear_magx();
      clear_magy();
      clear_magz();

    }

    static char const* field_number_to_name(const FieldNumber fieldNumber)
    {
      char const* name = nullptr;
      switch(fieldNumber)
      {
        case FieldNumber::ACCELX:
          name = ACCELX_NAME;
          break;
        case FieldNumber::ACCELY:
          name = ACCELY_NAME;
          break;
        case FieldNumber::ACCELZ:
          name = ACCELZ_NAME;
          break;
        case FieldNumber::GYROX:
          name = GYROX_NAME;
          break;
        case FieldNumber::GYROY:
          name = GYROY_NAME;
          break;
        case FieldNumber::GYROZ:
          name = GYROZ_NAME;
          break;
        case FieldNumber::MAGX:
          name = MAGX_NAME;
          break;
        case FieldNumber::MAGY:
          name = MAGY_NAME;
          break;
        case FieldNumber::MAGZ:
          name = MAGZ_NAME;
          break;
        default:
          name = "Invalid FieldNumber";
          break;
      }
      return name;
    }

#ifdef MSG_TO_STRING

    ::EmbeddedProto::string_view to_string(::EmbeddedProto::string_view& str) const
    {
      return this->to_string(str, 0, nullptr, true);
    }

    ::EmbeddedProto::string_view to_string(::EmbeddedProto::string_view& str, const uint32_t indent_level, char const* name, const bool first_field) const override
    {
      ::EmbeddedProto::string_view left_chars = str;
      int32_t n_chars_used = 0;

      if(!first_field)
      {
        // Add a comma behind the previous field.
        n_chars_used = snprintf(left_chars.data, left_chars.size, ",\n");
        if(0 < n_chars_used)
        {
          // Update the character pointer and characters left in the array.
          left_chars.data += n_chars_used;
          left_chars.size -= n_chars_used;
        }
      }

      if(nullptr != name)
      {
        if( 0 == indent_level)
        {
          n_chars_used = snprintf(left_chars.data, left_chars.size, "\"%s\": {\n", name);
        }
        else
        {
          n_chars_used = snprintf(left_chars.data, left_chars.size, "%*s\"%s\": {\n", indent_level, " ", name);
        }
      }
      else
      {
        if( 0 == indent_level)
        {
          n_chars_used = snprintf(left_chars.data, left_chars.size, "{\n");
        }
        else
        {
          n_chars_used = snprintf(left_chars.data, left_chars.size, "%*s{\n", indent_level, " ");
        }
      }
      
      if(0 < n_chars_used)
      {
        left_chars.data += n_chars_used;
        left_chars.size -= n_chars_used;
      }

      left_chars = accelx_.to_string(left_chars, indent_level + 2, ACCELX_NAME, true);
      left_chars = accely_.to_string(left_chars, indent_level + 2, ACCELY_NAME, false);
      left_chars = accelz_.to_string(left_chars, indent_level + 2, ACCELZ_NAME, false);
      left_chars = gyrox_.to_string(left_chars, indent_level + 2, GYROX_NAME, false);
      left_chars = gyroy_.to_string(left_chars, indent_level + 2, GYROY_NAME, false);
      left_chars = gyroz_.to_string(left_chars, indent_level + 2, GYROZ_NAME, false);
      left_chars = magx_.to_string(left_chars, indent_level + 2, MAGX_NAME, false);
      left_chars = magy_.to_string(left_chars, indent_level + 2, MAGY_NAME, false);
      left_chars = magz_.to_string(left_chars, indent_level + 2, MAGZ_NAME, false);
  
      if( 0 == indent_level) 
      {
        n_chars_used = snprintf(left_chars.data, left_chars.size, "\n}");
      }
      else 
      {
        n_chars_used = snprintf(left_chars.data, left_chars.size, "\n%*s}", indent_level, " ");
      }

      if(0 < n_chars_used)
      {
        left_chars.data += n_chars_used;
        left_chars.size -= n_chars_used;
      }

      return left_chars;
    }

#endif // End of MSG_TO_STRING

  private:


      EmbeddedProto::int32 accelx_ = 0;
      EmbeddedProto::int32 accely_ = 0;
      EmbeddedProto::int32 accelz_ = 0;
      EmbeddedProto::int32 gyrox_ = 0;
      EmbeddedProto::int32 gyroy_ = 0;
      EmbeddedProto::int32 gyroz_ = 0;
      EmbeddedProto::int32 magx_ = 0;
      EmbeddedProto::int32 magy_ = 0;
      EmbeddedProto::int32 magz_ = 0;

};

class IRTemperature final: public ::EmbeddedProto::MessageInterface
{
  public:
    IRTemperature() = default;
    IRTemperature(const IRTemperature& rhs )
    {
      set_ambient_temp(rhs.get_ambient_temp());
      set_object_temp(rhs.get_object_temp());
    }

    IRTemperature(const IRTemperature&& rhs ) noexcept
    {
      set_ambient_temp(rhs.get_ambient_temp());
      set_object_temp(rhs.get_object_temp());
    }

    ~IRTemperature() override = default;

    enum class FieldNumber : uint32_t
    {
      NOT_SET = 0,
      AMBIENT_TEMP = 1,
      OBJECT_TEMP = 2
    };

    IRTemperature& operator=(const IRTemperature& rhs)
    {
      set_ambient_temp(rhs.get_ambient_temp());
      set_object_temp(rhs.get_object_temp());
      return *this;
    }

    IRTemperature& operator=(const IRTemperature&& rhs) noexcept
    {
      set_ambient_temp(rhs.get_ambient_temp());
      set_object_temp(rhs.get_object_temp());
      return *this;
    }

    static constexpr char const* AMBIENT_TEMP_NAME = "ambient_temp";
    inline void clear_ambient_temp() { ambient_temp_.clear(); }
    inline void set_ambient_temp(const int32_t& value) { ambient_temp_ = value; }
    inline void set_ambient_temp(const int32_t&& value) { ambient_temp_ = value; }
    inline int32_t& mutable_ambient_temp() { return ambient_temp_.get(); }
    inline const int32_t& get_ambient_temp() const { return ambient_temp_.get(); }
    inline int32_t ambient_temp() const { return ambient_temp_.get(); }

    static constexpr char const* OBJECT_TEMP_NAME = "object_temp";
    inline void clear_object_temp() { object_temp_.clear(); }
    inline void set_object_temp(const int32_t& value) { object_temp_ = value; }
    inline void set_object_temp(const int32_t&& value) { object_temp_ = value; }
    inline int32_t& mutable_object_temp() { return object_temp_.get(); }
    inline const int32_t& get_object_temp() const { return object_temp_.get(); }
    inline int32_t object_temp() const { return object_temp_.get(); }


    ::EmbeddedProto::Error serialize(::EmbeddedProto::WriteBufferInterface& buffer) const override
    {
      ::EmbeddedProto::Error return_value = ::EmbeddedProto::Error::NO_ERRORS;

      if((0 != ambient_temp_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = ambient_temp_.serialize_with_id(static_cast<uint32_t>(FieldNumber::AMBIENT_TEMP), buffer, false);
      }

      if((0 != object_temp_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = object_temp_.serialize_with_id(static_cast<uint32_t>(FieldNumber::OBJECT_TEMP), buffer, false);
      }

      return return_value;
    };

    ::EmbeddedProto::Error deserialize(::EmbeddedProto::ReadBufferInterface& buffer) override
    {
      ::EmbeddedProto::Error return_value = ::EmbeddedProto::Error::NO_ERRORS;
      ::EmbeddedProto::WireFormatter::WireType wire_type = ::EmbeddedProto::WireFormatter::WireType::VARINT;
      uint32_t id_number = 0;
      FieldNumber id_tag = FieldNumber::NOT_SET;

      ::EmbeddedProto::Error tag_value = ::EmbeddedProto::WireFormatter::DeserializeTag(buffer, wire_type, id_number);
      while((::EmbeddedProto::Error::NO_ERRORS == return_value) && (::EmbeddedProto::Error::NO_ERRORS == tag_value))
      {
        id_tag = static_cast<FieldNumber>(id_number);
        switch(id_tag)
        {
          case FieldNumber::AMBIENT_TEMP:
            return_value = ambient_temp_.deserialize_check_type(buffer, wire_type);
            break;

          case FieldNumber::OBJECT_TEMP:
            return_value = object_temp_.deserialize_check_type(buffer, wire_type);
            break;

          case FieldNumber::NOT_SET:
            return_value = ::EmbeddedProto::Error::INVALID_FIELD_ID;
            break;

          default:
            return_value = skip_unknown_field(buffer, wire_type);
            break;
        }

        if(::EmbeddedProto::Error::NO_ERRORS == return_value)
        {
          // Read the next tag.
          tag_value = ::EmbeddedProto::WireFormatter::DeserializeTag(buffer, wire_type, id_number);
        }
      }

      // When an error was detect while reading the tag but no other errors where found, set it in the return value.
      if((::EmbeddedProto::Error::NO_ERRORS == return_value)
         && (::EmbeddedProto::Error::NO_ERRORS != tag_value)
         && (::EmbeddedProto::Error::END_OF_BUFFER != tag_value)) // The end of the buffer is not an array in this case.
      {
        return_value = tag_value;
      }

      return return_value;
    };

    void clear() override
    {
      clear_ambient_temp();
      clear_object_temp();

    }

    static char const* field_number_to_name(const FieldNumber fieldNumber)
    {
      char const* name = nullptr;
      switch(fieldNumber)
      {
        case FieldNumber::AMBIENT_TEMP:
          name = AMBIENT_TEMP_NAME;
          break;
        case FieldNumber::OBJECT_TEMP:
          name = OBJECT_TEMP_NAME;
          break;
        default:
          name = "Invalid FieldNumber";
          break;
      }
      return name;
    }

#ifdef MSG_TO_STRING

    ::EmbeddedProto::string_view to_string(::EmbeddedProto::string_view& str) const
    {
      return this->to_string(str, 0, nullptr, true);
    }

    ::EmbeddedProto::string_view to_string(::EmbeddedProto::string_view& str, const uint32_t indent_level, char const* name, const bool first_field) const override
    {
      ::EmbeddedProto::string_view left_chars = str;
      int32_t n_chars_used = 0;

      if(!first_field)
      {
        // Add a comma behind the previous field.
        n_chars_used = snprintf(left_chars.data, left_chars.size, ",\n");
        if(0 < n_chars_used)
        {
          // Update the character pointer and characters left in the array.
          left_chars.data += n_chars_used;
          left_chars.size -= n_chars_used;
        }
      }

      if(nullptr != name)
      {
        if( 0 == indent_level)
        {
          n_chars_used = snprintf(left_chars.data, left_chars.size, "\"%s\": {\n", name);
        }
        else
        {
          n_chars_used = snprintf(left_chars.data, left_chars.size, "%*s\"%s\": {\n", indent_level, " ", name);
        }
      }
      else
      {
        if( 0 == indent_level)
        {
          n_chars_used = snprintf(left_chars.data, left_chars.size, "{\n");
        }
        else
        {
          n_chars_used = snprintf(left_chars.data, left_chars.size, "%*s{\n", indent_level, " ");
        }
      }
      
      if(0 < n_chars_used)
      {
        left_chars.data += n_chars_used;
        left_chars.size -= n_chars_used;
      }

      left_chars = ambient_temp_.to_string(left_chars, indent_level + 2, AMBIENT_TEMP_NAME, true);
      left_chars = object_temp_.to_string(left_chars, indent_level + 2, OBJECT_TEMP_NAME, false);
  
      if( 0 == indent_level) 
      {
        n_chars_used = snprintf(left_chars.data, left_chars.size, "\n}");
      }
      else 
      {
        n_chars_used = snprintf(left_chars.data, left_chars.size, "\n%*s}", indent_level, " ");
      }

      if(0 < n_chars_used)
      {
        left_chars.data += n_chars_used;
        left_chars.size -= n_chars_used;
      }

      return left_chars;
    }

#endif // End of MSG_TO_STRING

  private:


      EmbeddedProto::int32 ambient_temp_ = 0;
      EmbeddedProto::int32 object_temp_ = 0;

};

class LRLoadCell final: public ::EmbeddedProto::MessageInterface
{
  public:
    LRLoadCell() = default;
    LRLoadCell(const LRLoadCell& rhs )
    {
      set_rocket_mass(rhs.get_rocket_mass());
    }

    LRLoadCell(const LRLoadCell&& rhs ) noexcept
    {
      set_rocket_mass(rhs.get_rocket_mass());
    }

    ~LRLoadCell() override = default;

    enum class FieldNumber : uint32_t
    {
      NOT_SET = 0,
      ROCKET_MASS = 1
    };

    LRLoadCell& operator=(const LRLoadCell& rhs)
    {
      set_rocket_mass(rhs.get_rocket_mass());
      return *this;
    }

    LRLoadCell& operator=(const LRLoadCell&& rhs) noexcept
    {
      set_rocket_mass(rhs.get_rocket_mass());
      return *this;
    }

    static constexpr char const* ROCKET_MASS_NAME = "rocket_mass";
    inline void clear_rocket_mass() { rocket_mass_.clear(); }
    inline void set_rocket_mass(const int32_t& value) { rocket_mass_ = value; }
    inline void set_rocket_mass(const int32_t&& value) { rocket_mass_ = value; }
    inline int32_t& mutable_rocket_mass() { return rocket_mass_.get(); }
    inline const int32_t& get_rocket_mass() const { return rocket_mass_.get(); }
    inline int32_t rocket_mass() const { return rocket_mass_.get(); }


    ::EmbeddedProto::Error serialize(::EmbeddedProto::WriteBufferInterface& buffer) const override
    {
      ::EmbeddedProto::Error return_value = ::EmbeddedProto::Error::NO_ERRORS;

      if((0 != rocket_mass_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = rocket_mass_.serialize_with_id(static_cast<uint32_t>(FieldNumber::ROCKET_MASS), buffer, false);
      }

      return return_value;
    };

    ::EmbeddedProto::Error deserialize(::EmbeddedProto::ReadBufferInterface& buffer) override
    {
      ::EmbeddedProto::Error return_value = ::EmbeddedProto::Error::NO_ERRORS;
      ::EmbeddedProto::WireFormatter::WireType wire_type = ::EmbeddedProto::WireFormatter::WireType::VARINT;
      uint32_t id_number = 0;
      FieldNumber id_tag = FieldNumber::NOT_SET;

      ::EmbeddedProto::Error tag_value = ::EmbeddedProto::WireFormatter::DeserializeTag(buffer, wire_type, id_number);
      while((::EmbeddedProto::Error::NO_ERRORS == return_value) && (::EmbeddedProto::Error::NO_ERRORS == tag_value))
      {
        id_tag = static_cast<FieldNumber>(id_number);
        switch(id_tag)
        {
          case FieldNumber::ROCKET_MASS:
            return_value = rocket_mass_.deserialize_check_type(buffer, wire_type);
            break;

          case FieldNumber::NOT_SET:
            return_value = ::EmbeddedProto::Error::INVALID_FIELD_ID;
            break;

          default:
            return_value = skip_unknown_field(buffer, wire_type);
            break;
        }

        if(::EmbeddedProto::Error::NO_ERRORS == return_value)
        {
          // Read the next tag.
          tag_value = ::EmbeddedProto::WireFormatter::DeserializeTag(buffer, wire_type, id_number);
        }
      }

      // When an error was detect while reading the tag but no other errors where found, set it in the return value.
      if((::EmbeddedProto::Error::NO_ERRORS == return_value)
         && (::EmbeddedProto::Error::NO_ERRORS != tag_value)
         && (::EmbeddedProto::Error::END_OF_BUFFER != tag_value)) // The end of the buffer is not an array in this case.
      {
        return_value = tag_value;
      }

      return return_value;
    };

    void clear() override
    {
      clear_rocket_mass();

    }

    static char const* field_number_to_name(const FieldNumber fieldNumber)
    {
      char const* name = nullptr;
      switch(fieldNumber)
      {
        case FieldNumber::ROCKET_MASS:
          name = ROCKET_MASS_NAME;
          break;
        default:
          name = "Invalid FieldNumber";
          break;
      }
      return name;
    }

#ifdef MSG_TO_STRING

    ::EmbeddedProto::string_view to_string(::EmbeddedProto::string_view& str) const
    {
      return this->to_string(str, 0, nullptr, true);
    }

    ::EmbeddedProto::string_view to_string(::EmbeddedProto::string_view& str, const uint32_t indent_level, char const* name, const bool first_field) const override
    {
      ::EmbeddedProto::string_view left_chars = str;
      int32_t n_chars_used = 0;

      if(!first_field)
      {
        // Add a comma behind the previous field.
        n_chars_used = snprintf(left_chars.data, left_chars.size, ",\n");
        if(0 < n_chars_used)
        {
          // Update the character pointer and characters left in the array.
          left_chars.data += n_chars_used;
          left_chars.size -= n_chars_used;
        }
      }

      if(nullptr != name)
      {
        if( 0 == indent_level)
        {
          n_chars_used = snprintf(left_chars.data, left_chars.size, "\"%s\": {\n", name);
        }
        else
        {
          n_chars_used = snprintf(left_chars.data, left_chars.size, "%*s\"%s\": {\n", indent_level, " ", name);
        }
      }
      else
      {
        if( 0 == indent_level)
        {
          n_chars_used = snprintf(left_chars.data, left_chars.size, "{\n");
        }
        else
        {
          n_chars_used = snprintf(left_chars.data, left_chars.size, "%*s{\n", indent_level, " ");
        }
      }
      
      if(0 < n_chars_used)
      {
        left_chars.data += n_chars_used;
        left_chars.size -= n_chars_used;
      }

      left_chars = rocket_mass_.to_string(left_chars, indent_level + 2, ROCKET_MASS_NAME, true);
  
      if( 0 == indent_level) 
      {
        n_chars_used = snprintf(left_chars.data, left_chars.size, "\n}");
      }
      else 
      {
        n_chars_used = snprintf(left_chars.data, left_chars.size, "\n%*s}", indent_level, " ");
      }

      if(0 < n_chars_used)
      {
        left_chars.data += n_chars_used;
        left_chars.size -= n_chars_used;
      }

      return left_chars;
    }

#endif // End of MSG_TO_STRING

  private:


      EmbeddedProto::int32 rocket_mass_ = 0;

};

class LatLong final: public ::EmbeddedProto::MessageInterface
{
  public:
    LatLong() = default;
    LatLong(const LatLong& rhs )
    {
      set_degrees(rhs.get_degrees());
      set_minutes(rhs.get_minutes());
    }

    LatLong(const LatLong&& rhs ) noexcept
    {
      set_degrees(rhs.get_degrees());
      set_minutes(rhs.get_minutes());
    }

    ~LatLong() override = default;

    enum class FieldNumber : uint32_t
    {
      NOT_SET = 0,
      DEGREES = 1,
      MINUTES = 2
    };

    LatLong& operator=(const LatLong& rhs)
    {
      set_degrees(rhs.get_degrees());
      set_minutes(rhs.get_minutes());
      return *this;
    }

    LatLong& operator=(const LatLong&& rhs) noexcept
    {
      set_degrees(rhs.get_degrees());
      set_minutes(rhs.get_minutes());
      return *this;
    }

    static constexpr char const* DEGREES_NAME = "degrees";
    inline void clear_degrees() { degrees_.clear(); }
    inline void set_degrees(const int32_t& value) { degrees_ = value; }
    inline void set_degrees(const int32_t&& value) { degrees_ = value; }
    inline int32_t& mutable_degrees() { return degrees_.get(); }
    inline const int32_t& get_degrees() const { return degrees_.get(); }
    inline int32_t degrees() const { return degrees_.get(); }

    static constexpr char const* MINUTES_NAME = "minutes";
    inline void clear_minutes() { minutes_.clear(); }
    inline void set_minutes(const int32_t& value) { minutes_ = value; }
    inline void set_minutes(const int32_t&& value) { minutes_ = value; }
    inline int32_t& mutable_minutes() { return minutes_.get(); }
    inline const int32_t& get_minutes() const { return minutes_.get(); }
    inline int32_t minutes() const { return minutes_.get(); }


    ::EmbeddedProto::Error serialize(::EmbeddedProto::WriteBufferInterface& buffer) const override
    {
      ::EmbeddedProto::Error return_value = ::EmbeddedProto::Error::NO_ERRORS;

      if((0 != degrees_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = degrees_.serialize_with_id(static_cast<uint32_t>(FieldNumber::DEGREES), buffer, false);
      }

      if((0 != minutes_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = minutes_.serialize_with_id(static_cast<uint32_t>(FieldNumber::MINUTES), buffer, false);
      }

      return return_value;
    };

    ::EmbeddedProto::Error deserialize(::EmbeddedProto::ReadBufferInterface& buffer) override
    {
      ::EmbeddedProto::Error return_value = ::EmbeddedProto::Error::NO_ERRORS;
      ::EmbeddedProto::WireFormatter::WireType wire_type = ::EmbeddedProto::WireFormatter::WireType::VARINT;
      uint32_t id_number = 0;
      FieldNumber id_tag = FieldNumber::NOT_SET;

      ::EmbeddedProto::Error tag_value = ::EmbeddedProto::WireFormatter::DeserializeTag(buffer, wire_type, id_number);
      while((::EmbeddedProto::Error::NO_ERRORS == return_value) && (::EmbeddedProto::Error::NO_ERRORS == tag_value))
      {
        id_tag = static_cast<FieldNumber>(id_number);
        switch(id_tag)
        {
          case FieldNumber::DEGREES:
            return_value = degrees_.deserialize_check_type(buffer, wire_type);
            break;

          case FieldNumber::MINUTES:
            return_value = minutes_.deserialize_check_type(buffer, wire_type);
            break;

          case FieldNumber::NOT_SET:
            return_value = ::EmbeddedProto::Error::INVALID_FIELD_ID;
            break;

          default:
            return_value = skip_unknown_field(buffer, wire_type);
            break;
        }

        if(::EmbeddedProto::Error::NO_ERRORS == return_value)
        {
          // Read the next tag.
          tag_value = ::EmbeddedProto::WireFormatter::DeserializeTag(buffer, wire_type, id_number);
        }
      }

      // When an error was detect while reading the tag but no other errors where found, set it in the return value.
      if((::EmbeddedProto::Error::NO_ERRORS == return_value)
         && (::EmbeddedProto::Error::NO_ERRORS != tag_value)
         && (::EmbeddedProto::Error::END_OF_BUFFER != tag_value)) // The end of the buffer is not an array in this case.
      {
        return_value = tag_value;
      }

      return return_value;
    };

    void clear() override
    {
      clear_degrees();
      clear_minutes();

    }

    static char const* field_number_to_name(const FieldNumber fieldNumber)
    {
      char const* name = nullptr;
      switch(fieldNumber)
      {
        case FieldNumber::DEGREES:
          name = DEGREES_NAME;
          break;
        case FieldNumber::MINUTES:
          name = MINUTES_NAME;
          break;
        default:
          name = "Invalid FieldNumber";
          break;
      }
      return name;
    }

#ifdef MSG_TO_STRING

    ::EmbeddedProto::string_view to_string(::EmbeddedProto::string_view& str) const
    {
      return this->to_string(str, 0, nullptr, true);
    }

    ::EmbeddedProto::string_view to_string(::EmbeddedProto::string_view& str, const uint32_t indent_level, char const* name, const bool first_field) const override
    {
      ::EmbeddedProto::string_view left_chars = str;
      int32_t n_chars_used = 0;

      if(!first_field)
      {
        // Add a comma behind the previous field.
        n_chars_used = snprintf(left_chars.data, left_chars.size, ",\n");
        if(0 < n_chars_used)
        {
          // Update the character pointer and characters left in the array.
          left_chars.data += n_chars_used;
          left_chars.size -= n_chars_used;
        }
      }

      if(nullptr != name)
      {
        if( 0 == indent_level)
        {
          n_chars_used = snprintf(left_chars.data, left_chars.size, "\"%s\": {\n", name);
        }
        else
        {
          n_chars_used = snprintf(left_chars.data, left_chars.size, "%*s\"%s\": {\n", indent_level, " ", name);
        }
      }
      else
      {
        if( 0 == indent_level)
        {
          n_chars_used = snprintf(left_chars.data, left_chars.size, "{\n");
        }
        else
        {
          n_chars_used = snprintf(left_chars.data, left_chars.size, "%*s{\n", indent_level, " ");
        }
      }
      
      if(0 < n_chars_used)
      {
        left_chars.data += n_chars_used;
        left_chars.size -= n_chars_used;
      }

      left_chars = degrees_.to_string(left_chars, indent_level + 2, DEGREES_NAME, true);
      left_chars = minutes_.to_string(left_chars, indent_level + 2, MINUTES_NAME, false);
  
      if( 0 == indent_level) 
      {
        n_chars_used = snprintf(left_chars.data, left_chars.size, "\n}");
      }
      else 
      {
        n_chars_used = snprintf(left_chars.data, left_chars.size, "\n%*s}", indent_level, " ");
      }

      if(0 < n_chars_used)
      {
        left_chars.data += n_chars_used;
        left_chars.size -= n_chars_used;
      }

      return left_chars;
    }

#endif // End of MSG_TO_STRING

  private:


      EmbeddedProto::int32 degrees_ = 0;
      EmbeddedProto::int32 minutes_ = 0;

};

class MEVState final: public ::EmbeddedProto::MessageInterface
{
  public:
    MEVState() = default;
    MEVState(const MEVState& rhs )
    {
      set_mev_open(rhs.get_mev_open());
    }

    MEVState(const MEVState&& rhs ) noexcept
    {
      set_mev_open(rhs.get_mev_open());
    }

    ~MEVState() override = default;

    enum class FieldNumber : uint32_t
    {
      NOT_SET = 0,
      MEV_OPEN = 1
    };

    MEVState& operator=(const MEVState& rhs)
    {
      set_mev_open(rhs.get_mev_open());
      return *this;
    }

    MEVState& operator=(const MEVState&& rhs) noexcept
    {
      set_mev_open(rhs.get_mev_open());
      return *this;
    }

    static constexpr char const* MEV_OPEN_NAME = "mev_open";
    inline void clear_mev_open() { mev_open_.clear(); }
    inline void set_mev_open(const bool& value) { mev_open_ = value; }
    inline void set_mev_open(const bool&& value) { mev_open_ = value; }
    inline bool& mutable_mev_open() { return mev_open_.get(); }
    inline const bool& get_mev_open() const { return mev_open_.get(); }
    inline bool mev_open() const { return mev_open_.get(); }


    ::EmbeddedProto::Error serialize(::EmbeddedProto::WriteBufferInterface& buffer) const override
    {
      ::EmbeddedProto::Error return_value = ::EmbeddedProto::Error::NO_ERRORS;

      if((false != mev_open_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = mev_open_.serialize_with_id(static_cast<uint32_t>(FieldNumber::MEV_OPEN), buffer, false);
      }

      return return_value;
    };

    ::EmbeddedProto::Error deserialize(::EmbeddedProto::ReadBufferInterface& buffer) override
    {
      ::EmbeddedProto::Error return_value = ::EmbeddedProto::Error::NO_ERRORS;
      ::EmbeddedProto::WireFormatter::WireType wire_type = ::EmbeddedProto::WireFormatter::WireType::VARINT;
      uint32_t id_number = 0;
      FieldNumber id_tag = FieldNumber::NOT_SET;

      ::EmbeddedProto::Error tag_value = ::EmbeddedProto::WireFormatter::DeserializeTag(buffer, wire_type, id_number);
      while((::EmbeddedProto::Error::NO_ERRORS == return_value) && (::EmbeddedProto::Error::NO_ERRORS == tag_value))
      {
        id_tag = static_cast<FieldNumber>(id_number);
        switch(id_tag)
        {
          case FieldNumber::MEV_OPEN:
            return_value = mev_open_.deserialize_check_type(buffer, wire_type);
            break;

          case FieldNumber::NOT_SET:
            return_value = ::EmbeddedProto::Error::INVALID_FIELD_ID;
            break;

          default:
            return_value = skip_unknown_field(buffer, wire_type);
            break;
        }

        if(::EmbeddedProto::Error::NO_ERRORS == return_value)
        {
          // Read the next tag.
          tag_value = ::EmbeddedProto::WireFormatter::DeserializeTag(buffer, wire_type, id_number);
        }
      }

      // When an error was detect while reading the tag but no other errors where found, set it in the return value.
      if((::EmbeddedProto::Error::NO_ERRORS == return_value)
         && (::EmbeddedProto::Error::NO_ERRORS != tag_value)
         && (::EmbeddedProto::Error::END_OF_BUFFER != tag_value)) // The end of the buffer is not an array in this case.
      {
        return_value = tag_value;
      }

      return return_value;
    };

    void clear() override
    {
      clear_mev_open();

    }

    static char const* field_number_to_name(const FieldNumber fieldNumber)
    {
      char const* name = nullptr;
      switch(fieldNumber)
      {
        case FieldNumber::MEV_OPEN:
          name = MEV_OPEN_NAME;
          break;
        default:
          name = "Invalid FieldNumber";
          break;
      }
      return name;
    }

#ifdef MSG_TO_STRING

    ::EmbeddedProto::string_view to_string(::EmbeddedProto::string_view& str) const
    {
      return this->to_string(str, 0, nullptr, true);
    }

    ::EmbeddedProto::string_view to_string(::EmbeddedProto::string_view& str, const uint32_t indent_level, char const* name, const bool first_field) const override
    {
      ::EmbeddedProto::string_view left_chars = str;
      int32_t n_chars_used = 0;

      if(!first_field)
      {
        // Add a comma behind the previous field.
        n_chars_used = snprintf(left_chars.data, left_chars.size, ",\n");
        if(0 < n_chars_used)
        {
          // Update the character pointer and characters left in the array.
          left_chars.data += n_chars_used;
          left_chars.size -= n_chars_used;
        }
      }

      if(nullptr != name)
      {
        if( 0 == indent_level)
        {
          n_chars_used = snprintf(left_chars.data, left_chars.size, "\"%s\": {\n", name);
        }
        else
        {
          n_chars_used = snprintf(left_chars.data, left_chars.size, "%*s\"%s\": {\n", indent_level, " ", name);
        }
      }
      else
      {
        if( 0 == indent_level)
        {
          n_chars_used = snprintf(left_chars.data, left_chars.size, "{\n");
        }
        else
        {
          n_chars_used = snprintf(left_chars.data, left_chars.size, "%*s{\n", indent_level, " ");
        }
      }
      
      if(0 < n_chars_used)
      {
        left_chars.data += n_chars_used;
        left_chars.size -= n_chars_used;
      }

      left_chars = mev_open_.to_string(left_chars, indent_level + 2, MEV_OPEN_NAME, true);
  
      if( 0 == indent_level) 
      {
        n_chars_used = snprintf(left_chars.data, left_chars.size, "\n}");
      }
      else 
      {
        n_chars_used = snprintf(left_chars.data, left_chars.size, "\n%*s}", indent_level, " ");
      }

      if(0 < n_chars_used)
      {
        left_chars.data += n_chars_used;
        left_chars.size -= n_chars_used;
      }

      return left_chars;
    }

#endif // End of MSG_TO_STRING

  private:


      EmbeddedProto::boolean mev_open_ = false;

};

class NOSLoadCell final: public ::EmbeddedProto::MessageInterface
{
  public:
    NOSLoadCell() = default;
    NOSLoadCell(const NOSLoadCell& rhs )
    {
      set_nos1_mass(rhs.get_nos1_mass());
      set_nos2_mass(rhs.get_nos2_mass());
    }

    NOSLoadCell(const NOSLoadCell&& rhs ) noexcept
    {
      set_nos1_mass(rhs.get_nos1_mass());
      set_nos2_mass(rhs.get_nos2_mass());
    }

    ~NOSLoadCell() override = default;

    enum class FieldNumber : uint32_t
    {
      NOT_SET = 0,
      NOS1_MASS = 1,
      NOS2_MASS = 2
    };

    NOSLoadCell& operator=(const NOSLoadCell& rhs)
    {
      set_nos1_mass(rhs.get_nos1_mass());
      set_nos2_mass(rhs.get_nos2_mass());
      return *this;
    }

    NOSLoadCell& operator=(const NOSLoadCell&& rhs) noexcept
    {
      set_nos1_mass(rhs.get_nos1_mass());
      set_nos2_mass(rhs.get_nos2_mass());
      return *this;
    }

    static constexpr char const* NOS1_MASS_NAME = "nos1_mass";
    inline void clear_nos1_mass() { nos1_mass_.clear(); }
    inline void set_nos1_mass(const int32_t& value) { nos1_mass_ = value; }
    inline void set_nos1_mass(const int32_t&& value) { nos1_mass_ = value; }
    inline int32_t& mutable_nos1_mass() { return nos1_mass_.get(); }
    inline const int32_t& get_nos1_mass() const { return nos1_mass_.get(); }
    inline int32_t nos1_mass() const { return nos1_mass_.get(); }

    static constexpr char const* NOS2_MASS_NAME = "nos2_mass";
    inline void clear_nos2_mass() { nos2_mass_.clear(); }
    inline void set_nos2_mass(const int32_t& value) { nos2_mass_ = value; }
    inline void set_nos2_mass(const int32_t&& value) { nos2_mass_ = value; }
    inline int32_t& mutable_nos2_mass() { return nos2_mass_.get(); }
    inline const int32_t& get_nos2_mass() const { return nos2_mass_.get(); }
    inline int32_t nos2_mass() const { return nos2_mass_.get(); }


    ::EmbeddedProto::Error serialize(::EmbeddedProto::WriteBufferInterface& buffer) const override
    {
      ::EmbeddedProto::Error return_value = ::EmbeddedProto::Error::NO_ERRORS;

      if((0 != nos1_mass_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = nos1_mass_.serialize_with_id(static_cast<uint32_t>(FieldNumber::NOS1_MASS), buffer, false);
      }

      if((0 != nos2_mass_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = nos2_mass_.serialize_with_id(static_cast<uint32_t>(FieldNumber::NOS2_MASS), buffer, false);
      }

      return return_value;
    };

    ::EmbeddedProto::Error deserialize(::EmbeddedProto::ReadBufferInterface& buffer) override
    {
      ::EmbeddedProto::Error return_value = ::EmbeddedProto::Error::NO_ERRORS;
      ::EmbeddedProto::WireFormatter::WireType wire_type = ::EmbeddedProto::WireFormatter::WireType::VARINT;
      uint32_t id_number = 0;
      FieldNumber id_tag = FieldNumber::NOT_SET;

      ::EmbeddedProto::Error tag_value = ::EmbeddedProto::WireFormatter::DeserializeTag(buffer, wire_type, id_number);
      while((::EmbeddedProto::Error::NO_ERRORS == return_value) && (::EmbeddedProto::Error::NO_ERRORS == tag_value))
      {
        id_tag = static_cast<FieldNumber>(id_number);
        switch(id_tag)
        {
          case FieldNumber::NOS1_MASS:
            return_value = nos1_mass_.deserialize_check_type(buffer, wire_type);
            break;

          case FieldNumber::NOS2_MASS:
            return_value = nos2_mass_.deserialize_check_type(buffer, wire_type);
            break;

          case FieldNumber::NOT_SET:
            return_value = ::EmbeddedProto::Error::INVALID_FIELD_ID;
            break;

          default:
            return_value = skip_unknown_field(buffer, wire_type);
            break;
        }

        if(::EmbeddedProto::Error::NO_ERRORS == return_value)
        {
          // Read the next tag.
          tag_value = ::EmbeddedProto::WireFormatter::DeserializeTag(buffer, wire_type, id_number);
        }
      }

      // When an error was detect while reading the tag but no other errors where found, set it in the return value.
      if((::EmbeddedProto::Error::NO_ERRORS == return_value)
         && (::EmbeddedProto::Error::NO_ERRORS != tag_value)
         && (::EmbeddedProto::Error::END_OF_BUFFER != tag_value)) // The end of the buffer is not an array in this case.
      {
        return_value = tag_value;
      }

      return return_value;
    };

    void clear() override
    {
      clear_nos1_mass();
      clear_nos2_mass();

    }

    static char const* field_number_to_name(const FieldNumber fieldNumber)
    {
      char const* name = nullptr;
      switch(fieldNumber)
      {
        case FieldNumber::NOS1_MASS:
          name = NOS1_MASS_NAME;
          break;
        case FieldNumber::NOS2_MASS:
          name = NOS2_MASS_NAME;
          break;
        default:
          name = "Invalid FieldNumber";
          break;
      }
      return name;
    }

#ifdef MSG_TO_STRING

    ::EmbeddedProto::string_view to_string(::EmbeddedProto::string_view& str) const
    {
      return this->to_string(str, 0, nullptr, true);
    }

    ::EmbeddedProto::string_view to_string(::EmbeddedProto::string_view& str, const uint32_t indent_level, char const* name, const bool first_field) const override
    {
      ::EmbeddedProto::string_view left_chars = str;
      int32_t n_chars_used = 0;

      if(!first_field)
      {
        // Add a comma behind the previous field.
        n_chars_used = snprintf(left_chars.data, left_chars.size, ",\n");
        if(0 < n_chars_used)
        {
          // Update the character pointer and characters left in the array.
          left_chars.data += n_chars_used;
          left_chars.size -= n_chars_used;
        }
      }

      if(nullptr != name)
      {
        if( 0 == indent_level)
        {
          n_chars_used = snprintf(left_chars.data, left_chars.size, "\"%s\": {\n", name);
        }
        else
        {
          n_chars_used = snprintf(left_chars.data, left_chars.size, "%*s\"%s\": {\n", indent_level, " ", name);
        }
      }
      else
      {
        if( 0 == indent_level)
        {
          n_chars_used = snprintf(left_chars.data, left_chars.size, "{\n");
        }
        else
        {
          n_chars_used = snprintf(left_chars.data, left_chars.size, "%*s{\n", indent_level, " ");
        }
      }
      
      if(0 < n_chars_used)
      {
        left_chars.data += n_chars_used;
        left_chars.size -= n_chars_used;
      }

      left_chars = nos1_mass_.to_string(left_chars, indent_level + 2, NOS1_MASS_NAME, true);
      left_chars = nos2_mass_.to_string(left_chars, indent_level + 2, NOS2_MASS_NAME, false);
  
      if( 0 == indent_level) 
      {
        n_chars_used = snprintf(left_chars.data, left_chars.size, "\n}");
      }
      else 
      {
        n_chars_used = snprintf(left_chars.data, left_chars.size, "\n%*s}", indent_level, " ");
      }

      if(0 < n_chars_used)
      {
        left_chars.data += n_chars_used;
        left_chars.size -= n_chars_used;
      }

      return left_chars;
    }

#endif // End of MSG_TO_STRING

  private:


      EmbeddedProto::int32 nos1_mass_ = 0;
      EmbeddedProto::int32 nos2_mass_ = 0;

};

class PBBPressure final: public ::EmbeddedProto::MessageInterface
{
  public:
    PBBPressure() = default;
    PBBPressure(const PBBPressure& rhs )
    {
      set_ib_pressure(rhs.get_ib_pressure());
      set_lower_pv_pressure(rhs.get_lower_pv_pressure());
    }

    PBBPressure(const PBBPressure&& rhs ) noexcept
    {
      set_ib_pressure(rhs.get_ib_pressure());
      set_lower_pv_pressure(rhs.get_lower_pv_pressure());
    }

    ~PBBPressure() override = default;

    enum class FieldNumber : uint32_t
    {
      NOT_SET = 0,
      IB_PRESSURE = 1,
      LOWER_PV_PRESSURE = 2
    };

    PBBPressure& operator=(const PBBPressure& rhs)
    {
      set_ib_pressure(rhs.get_ib_pressure());
      set_lower_pv_pressure(rhs.get_lower_pv_pressure());
      return *this;
    }

    PBBPressure& operator=(const PBBPressure&& rhs) noexcept
    {
      set_ib_pressure(rhs.get_ib_pressure());
      set_lower_pv_pressure(rhs.get_lower_pv_pressure());
      return *this;
    }

    static constexpr char const* IB_PRESSURE_NAME = "ib_pressure";
    inline void clear_ib_pressure() { ib_pressure_.clear(); }
    inline void set_ib_pressure(const int32_t& value) { ib_pressure_ = value; }
    inline void set_ib_pressure(const int32_t&& value) { ib_pressure_ = value; }
    inline int32_t& mutable_ib_pressure() { return ib_pressure_.get(); }
    inline const int32_t& get_ib_pressure() const { return ib_pressure_.get(); }
    inline int32_t ib_pressure() const { return ib_pressure_.get(); }

    static constexpr char const* LOWER_PV_PRESSURE_NAME = "lower_pv_pressure";
    inline void clear_lower_pv_pressure() { lower_pv_pressure_.clear(); }
    inline void set_lower_pv_pressure(const int32_t& value) { lower_pv_pressure_ = value; }
    inline void set_lower_pv_pressure(const int32_t&& value) { lower_pv_pressure_ = value; }
    inline int32_t& mutable_lower_pv_pressure() { return lower_pv_pressure_.get(); }
    inline const int32_t& get_lower_pv_pressure() const { return lower_pv_pressure_.get(); }
    inline int32_t lower_pv_pressure() const { return lower_pv_pressure_.get(); }


    ::EmbeddedProto::Error serialize(::EmbeddedProto::WriteBufferInterface& buffer) const override
    {
      ::EmbeddedProto::Error return_value = ::EmbeddedProto::Error::NO_ERRORS;

      if((0 != ib_pressure_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = ib_pressure_.serialize_with_id(static_cast<uint32_t>(FieldNumber::IB_PRESSURE), buffer, false);
      }

      if((0 != lower_pv_pressure_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = lower_pv_pressure_.serialize_with_id(static_cast<uint32_t>(FieldNumber::LOWER_PV_PRESSURE), buffer, false);
      }

      return return_value;
    };

    ::EmbeddedProto::Error deserialize(::EmbeddedProto::ReadBufferInterface& buffer) override
    {
      ::EmbeddedProto::Error return_value = ::EmbeddedProto::Error::NO_ERRORS;
      ::EmbeddedProto::WireFormatter::WireType wire_type = ::EmbeddedProto::WireFormatter::WireType::VARINT;
      uint32_t id_number = 0;
      FieldNumber id_tag = FieldNumber::NOT_SET;

      ::EmbeddedProto::Error tag_value = ::EmbeddedProto::WireFormatter::DeserializeTag(buffer, wire_type, id_number);
      while((::EmbeddedProto::Error::NO_ERRORS == return_value) && (::EmbeddedProto::Error::NO_ERRORS == tag_value))
      {
        id_tag = static_cast<FieldNumber>(id_number);
        switch(id_tag)
        {
          case FieldNumber::IB_PRESSURE:
            return_value = ib_pressure_.deserialize_check_type(buffer, wire_type);
            break;

          case FieldNumber::LOWER_PV_PRESSURE:
            return_value = lower_pv_pressure_.deserialize_check_type(buffer, wire_type);
            break;

          case FieldNumber::NOT_SET:
            return_value = ::EmbeddedProto::Error::INVALID_FIELD_ID;
            break;

          default:
            return_value = skip_unknown_field(buffer, wire_type);
            break;
        }

        if(::EmbeddedProto::Error::NO_ERRORS == return_value)
        {
          // Read the next tag.
          tag_value = ::EmbeddedProto::WireFormatter::DeserializeTag(buffer, wire_type, id_number);
        }
      }

      // When an error was detect while reading the tag but no other errors where found, set it in the return value.
      if((::EmbeddedProto::Error::NO_ERRORS == return_value)
         && (::EmbeddedProto::Error::NO_ERRORS != tag_value)
         && (::EmbeddedProto::Error::END_OF_BUFFER != tag_value)) // The end of the buffer is not an array in this case.
      {
        return_value = tag_value;
      }

      return return_value;
    };

    void clear() override
    {
      clear_ib_pressure();
      clear_lower_pv_pressure();

    }

    static char const* field_number_to_name(const FieldNumber fieldNumber)
    {
      char const* name = nullptr;
      switch(fieldNumber)
      {
        case FieldNumber::IB_PRESSURE:
          name = IB_PRESSURE_NAME;
          break;
        case FieldNumber::LOWER_PV_PRESSURE:
          name = LOWER_PV_PRESSURE_NAME;
          break;
        default:
          name = "Invalid FieldNumber";
          break;
      }
      return name;
    }

#ifdef MSG_TO_STRING

    ::EmbeddedProto::string_view to_string(::EmbeddedProto::string_view& str) const
    {
      return this->to_string(str, 0, nullptr, true);
    }

    ::EmbeddedProto::string_view to_string(::EmbeddedProto::string_view& str, const uint32_t indent_level, char const* name, const bool first_field) const override
    {
      ::EmbeddedProto::string_view left_chars = str;
      int32_t n_chars_used = 0;

      if(!first_field)
      {
        // Add a comma behind the previous field.
        n_chars_used = snprintf(left_chars.data, left_chars.size, ",\n");
        if(0 < n_chars_used)
        {
          // Update the character pointer and characters left in the array.
          left_chars.data += n_chars_used;
          left_chars.size -= n_chars_used;
        }
      }

      if(nullptr != name)
      {
        if( 0 == indent_level)
        {
          n_chars_used = snprintf(left_chars.data, left_chars.size, "\"%s\": {\n", name);
        }
        else
        {
          n_chars_used = snprintf(left_chars.data, left_chars.size, "%*s\"%s\": {\n", indent_level, " ", name);
        }
      }
      else
      {
        if( 0 == indent_level)
        {
          n_chars_used = snprintf(left_chars.data, left_chars.size, "{\n");
        }
        else
        {
          n_chars_used = snprintf(left_chars.data, left_chars.size, "%*s{\n", indent_level, " ");
        }
      }
      
      if(0 < n_chars_used)
      {
        left_chars.data += n_chars_used;
        left_chars.size -= n_chars_used;
      }

      left_chars = ib_pressure_.to_string(left_chars, indent_level + 2, IB_PRESSURE_NAME, true);
      left_chars = lower_pv_pressure_.to_string(left_chars, indent_level + 2, LOWER_PV_PRESSURE_NAME, false);
  
      if( 0 == indent_level) 
      {
        n_chars_used = snprintf(left_chars.data, left_chars.size, "\n}");
      }
      else 
      {
        n_chars_used = snprintf(left_chars.data, left_chars.size, "\n%*s}", indent_level, " ");
      }

      if(0 < n_chars_used)
      {
        left_chars.data += n_chars_used;
        left_chars.size -= n_chars_used;
      }

      return left_chars;
    }

#endif // End of MSG_TO_STRING

  private:


      EmbeddedProto::int32 ib_pressure_ = 0;
      EmbeddedProto::int32 lower_pv_pressure_ = 0;

};

class PBBTemp final: public ::EmbeddedProto::MessageInterface
{
  public:
    PBBTemp() = default;
    PBBTemp(const PBBTemp& rhs )
    {
      set_ib_temperature(rhs.get_ib_temperature());
      set_pv_temperature(rhs.get_pv_temperature());
    }

    PBBTemp(const PBBTemp&& rhs ) noexcept
    {
      set_ib_temperature(rhs.get_ib_temperature());
      set_pv_temperature(rhs.get_pv_temperature());
    }

    ~PBBTemp() override = default;

    enum class FieldNumber : uint32_t
    {
      NOT_SET = 0,
      IB_TEMPERATURE = 1,
      PV_TEMPERATURE = 2
    };

    PBBTemp& operator=(const PBBTemp& rhs)
    {
      set_ib_temperature(rhs.get_ib_temperature());
      set_pv_temperature(rhs.get_pv_temperature());
      return *this;
    }

    PBBTemp& operator=(const PBBTemp&& rhs) noexcept
    {
      set_ib_temperature(rhs.get_ib_temperature());
      set_pv_temperature(rhs.get_pv_temperature());
      return *this;
    }

    static constexpr char const* IB_TEMPERATURE_NAME = "ib_temperature";
    inline void clear_ib_temperature() { ib_temperature_.clear(); }
    inline void set_ib_temperature(const int32_t& value) { ib_temperature_ = value; }
    inline void set_ib_temperature(const int32_t&& value) { ib_temperature_ = value; }
    inline int32_t& mutable_ib_temperature() { return ib_temperature_.get(); }
    inline const int32_t& get_ib_temperature() const { return ib_temperature_.get(); }
    inline int32_t ib_temperature() const { return ib_temperature_.get(); }

    static constexpr char const* PV_TEMPERATURE_NAME = "pv_temperature";
    inline void clear_pv_temperature() { pv_temperature_.clear(); }
    inline void set_pv_temperature(const int32_t& value) { pv_temperature_ = value; }
    inline void set_pv_temperature(const int32_t&& value) { pv_temperature_ = value; }
    inline int32_t& mutable_pv_temperature() { return pv_temperature_.get(); }
    inline const int32_t& get_pv_temperature() const { return pv_temperature_.get(); }
    inline int32_t pv_temperature() const { return pv_temperature_.get(); }


    ::EmbeddedProto::Error serialize(::EmbeddedProto::WriteBufferInterface& buffer) const override
    {
      ::EmbeddedProto::Error return_value = ::EmbeddedProto::Error::NO_ERRORS;

      if((0 != ib_temperature_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = ib_temperature_.serialize_with_id(static_cast<uint32_t>(FieldNumber::IB_TEMPERATURE), buffer, false);
      }

      if((0 != pv_temperature_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = pv_temperature_.serialize_with_id(static_cast<uint32_t>(FieldNumber::PV_TEMPERATURE), buffer, false);
      }

      return return_value;
    };

    ::EmbeddedProto::Error deserialize(::EmbeddedProto::ReadBufferInterface& buffer) override
    {
      ::EmbeddedProto::Error return_value = ::EmbeddedProto::Error::NO_ERRORS;
      ::EmbeddedProto::WireFormatter::WireType wire_type = ::EmbeddedProto::WireFormatter::WireType::VARINT;
      uint32_t id_number = 0;
      FieldNumber id_tag = FieldNumber::NOT_SET;

      ::EmbeddedProto::Error tag_value = ::EmbeddedProto::WireFormatter::DeserializeTag(buffer, wire_type, id_number);
      while((::EmbeddedProto::Error::NO_ERRORS == return_value) && (::EmbeddedProto::Error::NO_ERRORS == tag_value))
      {
        id_tag = static_cast<FieldNumber>(id_number);
        switch(id_tag)
        {
          case FieldNumber::IB_TEMPERATURE:
            return_value = ib_temperature_.deserialize_check_type(buffer, wire_type);
            break;

          case FieldNumber::PV_TEMPERATURE:
            return_value = pv_temperature_.deserialize_check_type(buffer, wire_type);
            break;

          case FieldNumber::NOT_SET:
            return_value = ::EmbeddedProto::Error::INVALID_FIELD_ID;
            break;

          default:
            return_value = skip_unknown_field(buffer, wire_type);
            break;
        }

        if(::EmbeddedProto::Error::NO_ERRORS == return_value)
        {
          // Read the next tag.
          tag_value = ::EmbeddedProto::WireFormatter::DeserializeTag(buffer, wire_type, id_number);
        }
      }

      // When an error was detect while reading the tag but no other errors where found, set it in the return value.
      if((::EmbeddedProto::Error::NO_ERRORS == return_value)
         && (::EmbeddedProto::Error::NO_ERRORS != tag_value)
         && (::EmbeddedProto::Error::END_OF_BUFFER != tag_value)) // The end of the buffer is not an array in this case.
      {
        return_value = tag_value;
      }

      return return_value;
    };

    void clear() override
    {
      clear_ib_temperature();
      clear_pv_temperature();

    }

    static char const* field_number_to_name(const FieldNumber fieldNumber)
    {
      char const* name = nullptr;
      switch(fieldNumber)
      {
        case FieldNumber::IB_TEMPERATURE:
          name = IB_TEMPERATURE_NAME;
          break;
        case FieldNumber::PV_TEMPERATURE:
          name = PV_TEMPERATURE_NAME;
          break;
        default:
          name = "Invalid FieldNumber";
          break;
      }
      return name;
    }

#ifdef MSG_TO_STRING

    ::EmbeddedProto::string_view to_string(::EmbeddedProto::string_view& str) const
    {
      return this->to_string(str, 0, nullptr, true);
    }

    ::EmbeddedProto::string_view to_string(::EmbeddedProto::string_view& str, const uint32_t indent_level, char const* name, const bool first_field) const override
    {
      ::EmbeddedProto::string_view left_chars = str;
      int32_t n_chars_used = 0;

      if(!first_field)
      {
        // Add a comma behind the previous field.
        n_chars_used = snprintf(left_chars.data, left_chars.size, ",\n");
        if(0 < n_chars_used)
        {
          // Update the character pointer and characters left in the array.
          left_chars.data += n_chars_used;
          left_chars.size -= n_chars_used;
        }
      }

      if(nullptr != name)
      {
        if( 0 == indent_level)
        {
          n_chars_used = snprintf(left_chars.data, left_chars.size, "\"%s\": {\n", name);
        }
        else
        {
          n_chars_used = snprintf(left_chars.data, left_chars.size, "%*s\"%s\": {\n", indent_level, " ", name);
        }
      }
      else
      {
        if( 0 == indent_level)
        {
          n_chars_used = snprintf(left_chars.data, left_chars.size, "{\n");
        }
        else
        {
          n_chars_used = snprintf(left_chars.data, left_chars.size, "%*s{\n", indent_level, " ");
        }
      }
      
      if(0 < n_chars_used)
      {
        left_chars.data += n_chars_used;
        left_chars.size -= n_chars_used;
      }

      left_chars = ib_temperature_.to_string(left_chars, indent_level + 2, IB_TEMPERATURE_NAME, true);
      left_chars = pv_temperature_.to_string(left_chars, indent_level + 2, PV_TEMPERATURE_NAME, false);
  
      if( 0 == indent_level) 
      {
        n_chars_used = snprintf(left_chars.data, left_chars.size, "\n}");
      }
      else 
      {
        n_chars_used = snprintf(left_chars.data, left_chars.size, "\n%*s}", indent_level, " ");
      }

      if(0 < n_chars_used)
      {
        left_chars.data += n_chars_used;
        left_chars.size -= n_chars_used;
      }

      return left_chars;
    }

#endif // End of MSG_TO_STRING

  private:


      EmbeddedProto::int32 ib_temperature_ = 0;
      EmbeddedProto::int32 pv_temperature_ = 0;

};

class PadBoxStatus final: public ::EmbeddedProto::MessageInterface
{
  public:
    PadBoxStatus() = default;
    PadBoxStatus(const PadBoxStatus& rhs )
    {
      set_cont1(rhs.get_cont1());
      set_cont2(rhs.get_cont2());
      set_box1_on(rhs.get_box1_on());
      set_box2_on(rhs.get_box2_on());
    }

    PadBoxStatus(const PadBoxStatus&& rhs ) noexcept
    {
      set_cont1(rhs.get_cont1());
      set_cont2(rhs.get_cont2());
      set_box1_on(rhs.get_box1_on());
      set_box2_on(rhs.get_box2_on());
    }

    ~PadBoxStatus() override = default;

    enum class FieldNumber : uint32_t
    {
      NOT_SET = 0,
      CONT1 = 1,
      CONT2 = 2,
      BOX1_ON = 3,
      BOX2_ON = 4
    };

    PadBoxStatus& operator=(const PadBoxStatus& rhs)
    {
      set_cont1(rhs.get_cont1());
      set_cont2(rhs.get_cont2());
      set_box1_on(rhs.get_box1_on());
      set_box2_on(rhs.get_box2_on());
      return *this;
    }

    PadBoxStatus& operator=(const PadBoxStatus&& rhs) noexcept
    {
      set_cont1(rhs.get_cont1());
      set_cont2(rhs.get_cont2());
      set_box1_on(rhs.get_box1_on());
      set_box2_on(rhs.get_box2_on());
      return *this;
    }

    static constexpr char const* CONT1_NAME = "cont1";
    inline void clear_cont1() { cont1_.clear(); }
    inline void set_cont1(const bool& value) { cont1_ = value; }
    inline void set_cont1(const bool&& value) { cont1_ = value; }
    inline bool& mutable_cont1() { return cont1_.get(); }
    inline const bool& get_cont1() const { return cont1_.get(); }
    inline bool cont1() const { return cont1_.get(); }

    static constexpr char const* CONT2_NAME = "cont2";
    inline void clear_cont2() { cont2_.clear(); }
    inline void set_cont2(const bool& value) { cont2_ = value; }
    inline void set_cont2(const bool&& value) { cont2_ = value; }
    inline bool& mutable_cont2() { return cont2_.get(); }
    inline const bool& get_cont2() const { return cont2_.get(); }
    inline bool cont2() const { return cont2_.get(); }

    static constexpr char const* BOX1_ON_NAME = "box1_on";
    inline void clear_box1_on() { box1_on_.clear(); }
    inline void set_box1_on(const bool& value) { box1_on_ = value; }
    inline void set_box1_on(const bool&& value) { box1_on_ = value; }
    inline bool& mutable_box1_on() { return box1_on_.get(); }
    inline const bool& get_box1_on() const { return box1_on_.get(); }
    inline bool box1_on() const { return box1_on_.get(); }

    static constexpr char const* BOX2_ON_NAME = "box2_on";
    inline void clear_box2_on() { box2_on_.clear(); }
    inline void set_box2_on(const bool& value) { box2_on_ = value; }
    inline void set_box2_on(const bool&& value) { box2_on_ = value; }
    inline bool& mutable_box2_on() { return box2_on_.get(); }
    inline const bool& get_box2_on() const { return box2_on_.get(); }
    inline bool box2_on() const { return box2_on_.get(); }


    ::EmbeddedProto::Error serialize(::EmbeddedProto::WriteBufferInterface& buffer) const override
    {
      ::EmbeddedProto::Error return_value = ::EmbeddedProto::Error::NO_ERRORS;

      if((false != cont1_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = cont1_.serialize_with_id(static_cast<uint32_t>(FieldNumber::CONT1), buffer, false);
      }

      if((false != cont2_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = cont2_.serialize_with_id(static_cast<uint32_t>(FieldNumber::CONT2), buffer, false);
      }

      if((false != box1_on_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = box1_on_.serialize_with_id(static_cast<uint32_t>(FieldNumber::BOX1_ON), buffer, false);
      }

      if((false != box2_on_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = box2_on_.serialize_with_id(static_cast<uint32_t>(FieldNumber::BOX2_ON), buffer, false);
      }

      return return_value;
    };

    ::EmbeddedProto::Error deserialize(::EmbeddedProto::ReadBufferInterface& buffer) override
    {
      ::EmbeddedProto::Error return_value = ::EmbeddedProto::Error::NO_ERRORS;
      ::EmbeddedProto::WireFormatter::WireType wire_type = ::EmbeddedProto::WireFormatter::WireType::VARINT;
      uint32_t id_number = 0;
      FieldNumber id_tag = FieldNumber::NOT_SET;

      ::EmbeddedProto::Error tag_value = ::EmbeddedProto::WireFormatter::DeserializeTag(buffer, wire_type, id_number);
      while((::EmbeddedProto::Error::NO_ERRORS == return_value) && (::EmbeddedProto::Error::NO_ERRORS == tag_value))
      {
        id_tag = static_cast<FieldNumber>(id_number);
        switch(id_tag)
        {
          case FieldNumber::CONT1:
            return_value = cont1_.deserialize_check_type(buffer, wire_type);
            break;

          case FieldNumber::CONT2:
            return_value = cont2_.deserialize_check_type(buffer, wire_type);
            break;

          case FieldNumber::BOX1_ON:
            return_value = box1_on_.deserialize_check_type(buffer, wire_type);
            break;

          case FieldNumber::BOX2_ON:
            return_value = box2_on_.deserialize_check_type(buffer, wire_type);
            break;

          case FieldNumber::NOT_SET:
            return_value = ::EmbeddedProto::Error::INVALID_FIELD_ID;
            break;

          default:
            return_value = skip_unknown_field(buffer, wire_type);
            break;
        }

        if(::EmbeddedProto::Error::NO_ERRORS == return_value)
        {
          // Read the next tag.
          tag_value = ::EmbeddedProto::WireFormatter::DeserializeTag(buffer, wire_type, id_number);
        }
      }

      // When an error was detect while reading the tag but no other errors where found, set it in the return value.
      if((::EmbeddedProto::Error::NO_ERRORS == return_value)
         && (::EmbeddedProto::Error::NO_ERRORS != tag_value)
         && (::EmbeddedProto::Error::END_OF_BUFFER != tag_value)) // The end of the buffer is not an array in this case.
      {
        return_value = tag_value;
      }

      return return_value;
    };

    void clear() override
    {
      clear_cont1();
      clear_cont2();
      clear_box1_on();
      clear_box2_on();

    }

    static char const* field_number_to_name(const FieldNumber fieldNumber)
    {
      char const* name = nullptr;
      switch(fieldNumber)
      {
        case FieldNumber::CONT1:
          name = CONT1_NAME;
          break;
        case FieldNumber::CONT2:
          name = CONT2_NAME;
          break;
        case FieldNumber::BOX1_ON:
          name = BOX1_ON_NAME;
          break;
        case FieldNumber::BOX2_ON:
          name = BOX2_ON_NAME;
          break;
        default:
          name = "Invalid FieldNumber";
          break;
      }
      return name;
    }

#ifdef MSG_TO_STRING

    ::EmbeddedProto::string_view to_string(::EmbeddedProto::string_view& str) const
    {
      return this->to_string(str, 0, nullptr, true);
    }

    ::EmbeddedProto::string_view to_string(::EmbeddedProto::string_view& str, const uint32_t indent_level, char const* name, const bool first_field) const override
    {
      ::EmbeddedProto::string_view left_chars = str;
      int32_t n_chars_used = 0;

      if(!first_field)
      {
        // Add a comma behind the previous field.
        n_chars_used = snprintf(left_chars.data, left_chars.size, ",\n");
        if(0 < n_chars_used)
        {
          // Update the character pointer and characters left in the array.
          left_chars.data += n_chars_used;
          left_chars.size -= n_chars_used;
        }
      }

      if(nullptr != name)
      {
        if( 0 == indent_level)
        {
          n_chars_used = snprintf(left_chars.data, left_chars.size, "\"%s\": {\n", name);
        }
        else
        {
          n_chars_used = snprintf(left_chars.data, left_chars.size, "%*s\"%s\": {\n", indent_level, " ", name);
        }
      }
      else
      {
        if( 0 == indent_level)
        {
          n_chars_used = snprintf(left_chars.data, left_chars.size, "{\n");
        }
        else
        {
          n_chars_used = snprintf(left_chars.data, left_chars.size, "%*s{\n", indent_level, " ");
        }
      }
      
      if(0 < n_chars_used)
      {
        left_chars.data += n_chars_used;
        left_chars.size -= n_chars_used;
      }

      left_chars = cont1_.to_string(left_chars, indent_level + 2, CONT1_NAME, true);
      left_chars = cont2_.to_string(left_chars, indent_level + 2, CONT2_NAME, false);
      left_chars = box1_on_.to_string(left_chars, indent_level + 2, BOX1_ON_NAME, false);
      left_chars = box2_on_.to_string(left_chars, indent_level + 2, BOX2_ON_NAME, false);
  
      if( 0 == indent_level) 
      {
        n_chars_used = snprintf(left_chars.data, left_chars.size, "\n}");
      }
      else 
      {
        n_chars_used = snprintf(left_chars.data, left_chars.size, "\n%*s}", indent_level, " ");
      }

      if(0 < n_chars_used)
      {
        left_chars.data += n_chars_used;
        left_chars.size -= n_chars_used;
      }

      return left_chars;
    }

#endif // End of MSG_TO_STRING

  private:


      EmbeddedProto::boolean cont1_ = false;
      EmbeddedProto::boolean cont2_ = false;
      EmbeddedProto::boolean box1_on_ = false;
      EmbeddedProto::boolean box2_on_ = false;

};

class RCUPressure final: public ::EmbeddedProto::MessageInterface
{
  public:
    RCUPressure() = default;
    RCUPressure(const RCUPressure& rhs )
    {
      set_pt1_pressure(rhs.get_pt1_pressure());
      set_pt2_pressure(rhs.get_pt2_pressure());
      set_pt3_pressure(rhs.get_pt3_pressure());
      set_pt4_pressure(rhs.get_pt4_pressure());
    }

    RCUPressure(const RCUPressure&& rhs ) noexcept
    {
      set_pt1_pressure(rhs.get_pt1_pressure());
      set_pt2_pressure(rhs.get_pt2_pressure());
      set_pt3_pressure(rhs.get_pt3_pressure());
      set_pt4_pressure(rhs.get_pt4_pressure());
    }

    ~RCUPressure() override = default;

    enum class FieldNumber : uint32_t
    {
      NOT_SET = 0,
      PT1_PRESSURE = 1,
      PT2_PRESSURE = 2,
      PT3_PRESSURE = 3,
      PT4_PRESSURE = 4
    };

    RCUPressure& operator=(const RCUPressure& rhs)
    {
      set_pt1_pressure(rhs.get_pt1_pressure());
      set_pt2_pressure(rhs.get_pt2_pressure());
      set_pt3_pressure(rhs.get_pt3_pressure());
      set_pt4_pressure(rhs.get_pt4_pressure());
      return *this;
    }

    RCUPressure& operator=(const RCUPressure&& rhs) noexcept
    {
      set_pt1_pressure(rhs.get_pt1_pressure());
      set_pt2_pressure(rhs.get_pt2_pressure());
      set_pt3_pressure(rhs.get_pt3_pressure());
      set_pt4_pressure(rhs.get_pt4_pressure());
      return *this;
    }

    static constexpr char const* PT1_PRESSURE_NAME = "pt1_pressure";
    inline void clear_pt1_pressure() { pt1_pressure_.clear(); }
    inline void set_pt1_pressure(const int32_t& value) { pt1_pressure_ = value; }
    inline void set_pt1_pressure(const int32_t&& value) { pt1_pressure_ = value; }
    inline int32_t& mutable_pt1_pressure() { return pt1_pressure_.get(); }
    inline const int32_t& get_pt1_pressure() const { return pt1_pressure_.get(); }
    inline int32_t pt1_pressure() const { return pt1_pressure_.get(); }

    static constexpr char const* PT2_PRESSURE_NAME = "pt2_pressure";
    inline void clear_pt2_pressure() { pt2_pressure_.clear(); }
    inline void set_pt2_pressure(const int32_t& value) { pt2_pressure_ = value; }
    inline void set_pt2_pressure(const int32_t&& value) { pt2_pressure_ = value; }
    inline int32_t& mutable_pt2_pressure() { return pt2_pressure_.get(); }
    inline const int32_t& get_pt2_pressure() const { return pt2_pressure_.get(); }
    inline int32_t pt2_pressure() const { return pt2_pressure_.get(); }

    static constexpr char const* PT3_PRESSURE_NAME = "pt3_pressure";
    inline void clear_pt3_pressure() { pt3_pressure_.clear(); }
    inline void set_pt3_pressure(const int32_t& value) { pt3_pressure_ = value; }
    inline void set_pt3_pressure(const int32_t&& value) { pt3_pressure_ = value; }
    inline int32_t& mutable_pt3_pressure() { return pt3_pressure_.get(); }
    inline const int32_t& get_pt3_pressure() const { return pt3_pressure_.get(); }
    inline int32_t pt3_pressure() const { return pt3_pressure_.get(); }

    static constexpr char const* PT4_PRESSURE_NAME = "pt4_pressure";
    inline void clear_pt4_pressure() { pt4_pressure_.clear(); }
    inline void set_pt4_pressure(const int32_t& value) { pt4_pressure_ = value; }
    inline void set_pt4_pressure(const int32_t&& value) { pt4_pressure_ = value; }
    inline int32_t& mutable_pt4_pressure() { return pt4_pressure_.get(); }
    inline const int32_t& get_pt4_pressure() const { return pt4_pressure_.get(); }
    inline int32_t pt4_pressure() const { return pt4_pressure_.get(); }


    ::EmbeddedProto::Error serialize(::EmbeddedProto::WriteBufferInterface& buffer) const override
    {
      ::EmbeddedProto::Error return_value = ::EmbeddedProto::Error::NO_ERRORS;

      if((0 != pt1_pressure_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = pt1_pressure_.serialize_with_id(static_cast<uint32_t>(FieldNumber::PT1_PRESSURE), buffer, false);
      }

      if((0 != pt2_pressure_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = pt2_pressure_.serialize_with_id(static_cast<uint32_t>(FieldNumber::PT2_PRESSURE), buffer, false);
      }

      if((0 != pt3_pressure_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = pt3_pressure_.serialize_with_id(static_cast<uint32_t>(FieldNumber::PT3_PRESSURE), buffer, false);
      }

      if((0 != pt4_pressure_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = pt4_pressure_.serialize_with_id(static_cast<uint32_t>(FieldNumber::PT4_PRESSURE), buffer, false);
      }

      return return_value;
    };

    ::EmbeddedProto::Error deserialize(::EmbeddedProto::ReadBufferInterface& buffer) override
    {
      ::EmbeddedProto::Error return_value = ::EmbeddedProto::Error::NO_ERRORS;
      ::EmbeddedProto::WireFormatter::WireType wire_type = ::EmbeddedProto::WireFormatter::WireType::VARINT;
      uint32_t id_number = 0;
      FieldNumber id_tag = FieldNumber::NOT_SET;

      ::EmbeddedProto::Error tag_value = ::EmbeddedProto::WireFormatter::DeserializeTag(buffer, wire_type, id_number);
      while((::EmbeddedProto::Error::NO_ERRORS == return_value) && (::EmbeddedProto::Error::NO_ERRORS == tag_value))
      {
        id_tag = static_cast<FieldNumber>(id_number);
        switch(id_tag)
        {
          case FieldNumber::PT1_PRESSURE:
            return_value = pt1_pressure_.deserialize_check_type(buffer, wire_type);
            break;

          case FieldNumber::PT2_PRESSURE:
            return_value = pt2_pressure_.deserialize_check_type(buffer, wire_type);
            break;

          case FieldNumber::PT3_PRESSURE:
            return_value = pt3_pressure_.deserialize_check_type(buffer, wire_type);
            break;

          case FieldNumber::PT4_PRESSURE:
            return_value = pt4_pressure_.deserialize_check_type(buffer, wire_type);
            break;

          case FieldNumber::NOT_SET:
            return_value = ::EmbeddedProto::Error::INVALID_FIELD_ID;
            break;

          default:
            return_value = skip_unknown_field(buffer, wire_type);
            break;
        }

        if(::EmbeddedProto::Error::NO_ERRORS == return_value)
        {
          // Read the next tag.
          tag_value = ::EmbeddedProto::WireFormatter::DeserializeTag(buffer, wire_type, id_number);
        }
      }

      // When an error was detect while reading the tag but no other errors where found, set it in the return value.
      if((::EmbeddedProto::Error::NO_ERRORS == return_value)
         && (::EmbeddedProto::Error::NO_ERRORS != tag_value)
         && (::EmbeddedProto::Error::END_OF_BUFFER != tag_value)) // The end of the buffer is not an array in this case.
      {
        return_value = tag_value;
      }

      return return_value;
    };

    void clear() override
    {
      clear_pt1_pressure();
      clear_pt2_pressure();
      clear_pt3_pressure();
      clear_pt4_pressure();

    }

    static char const* field_number_to_name(const FieldNumber fieldNumber)
    {
      char const* name = nullptr;
      switch(fieldNumber)
      {
        case FieldNumber::PT1_PRESSURE:
          name = PT1_PRESSURE_NAME;
          break;
        case FieldNumber::PT2_PRESSURE:
          name = PT2_PRESSURE_NAME;
          break;
        case FieldNumber::PT3_PRESSURE:
          name = PT3_PRESSURE_NAME;
          break;
        case FieldNumber::PT4_PRESSURE:
          name = PT4_PRESSURE_NAME;
          break;
        default:
          name = "Invalid FieldNumber";
          break;
      }
      return name;
    }

#ifdef MSG_TO_STRING

    ::EmbeddedProto::string_view to_string(::EmbeddedProto::string_view& str) const
    {
      return this->to_string(str, 0, nullptr, true);
    }

    ::EmbeddedProto::string_view to_string(::EmbeddedProto::string_view& str, const uint32_t indent_level, char const* name, const bool first_field) const override
    {
      ::EmbeddedProto::string_view left_chars = str;
      int32_t n_chars_used = 0;

      if(!first_field)
      {
        // Add a comma behind the previous field.
        n_chars_used = snprintf(left_chars.data, left_chars.size, ",\n");
        if(0 < n_chars_used)
        {
          // Update the character pointer and characters left in the array.
          left_chars.data += n_chars_used;
          left_chars.size -= n_chars_used;
        }
      }

      if(nullptr != name)
      {
        if( 0 == indent_level)
        {
          n_chars_used = snprintf(left_chars.data, left_chars.size, "\"%s\": {\n", name);
        }
        else
        {
          n_chars_used = snprintf(left_chars.data, left_chars.size, "%*s\"%s\": {\n", indent_level, " ", name);
        }
      }
      else
      {
        if( 0 == indent_level)
        {
          n_chars_used = snprintf(left_chars.data, left_chars.size, "{\n");
        }
        else
        {
          n_chars_used = snprintf(left_chars.data, left_chars.size, "%*s{\n", indent_level, " ");
        }
      }
      
      if(0 < n_chars_used)
      {
        left_chars.data += n_chars_used;
        left_chars.size -= n_chars_used;
      }

      left_chars = pt1_pressure_.to_string(left_chars, indent_level + 2, PT1_PRESSURE_NAME, true);
      left_chars = pt2_pressure_.to_string(left_chars, indent_level + 2, PT2_PRESSURE_NAME, false);
      left_chars = pt3_pressure_.to_string(left_chars, indent_level + 2, PT3_PRESSURE_NAME, false);
      left_chars = pt4_pressure_.to_string(left_chars, indent_level + 2, PT4_PRESSURE_NAME, false);
  
      if( 0 == indent_level) 
      {
        n_chars_used = snprintf(left_chars.data, left_chars.size, "\n}");
      }
      else 
      {
        n_chars_used = snprintf(left_chars.data, left_chars.size, "\n%*s}", indent_level, " ");
      }

      if(0 < n_chars_used)
      {
        left_chars.data += n_chars_used;
        left_chars.size -= n_chars_used;
      }

      return left_chars;
    }

#endif // End of MSG_TO_STRING

  private:


      EmbeddedProto::int32 pt1_pressure_ = 0;
      EmbeddedProto::int32 pt2_pressure_ = 0;
      EmbeddedProto::int32 pt3_pressure_ = 0;
      EmbeddedProto::int32 pt4_pressure_ = 0;

};

class RCUTemp final: public ::EmbeddedProto::MessageInterface
{
  public:
    RCUTemp() = default;
    RCUTemp(const RCUTemp& rhs )
    {
      set_tc1_temp(rhs.get_tc1_temp());
      set_tc2_temp(rhs.get_tc2_temp());
    }

    RCUTemp(const RCUTemp&& rhs ) noexcept
    {
      set_tc1_temp(rhs.get_tc1_temp());
      set_tc2_temp(rhs.get_tc2_temp());
    }

    ~RCUTemp() override = default;

    enum class FieldNumber : uint32_t
    {
      NOT_SET = 0,
      TC1_TEMP = 1,
      TC2_TEMP = 2
    };

    RCUTemp& operator=(const RCUTemp& rhs)
    {
      set_tc1_temp(rhs.get_tc1_temp());
      set_tc2_temp(rhs.get_tc2_temp());
      return *this;
    }

    RCUTemp& operator=(const RCUTemp&& rhs) noexcept
    {
      set_tc1_temp(rhs.get_tc1_temp());
      set_tc2_temp(rhs.get_tc2_temp());
      return *this;
    }

    static constexpr char const* TC1_TEMP_NAME = "tc1_temp";
    inline void clear_tc1_temp() { tc1_temp_.clear(); }
    inline void set_tc1_temp(const int32_t& value) { tc1_temp_ = value; }
    inline void set_tc1_temp(const int32_t&& value) { tc1_temp_ = value; }
    inline int32_t& mutable_tc1_temp() { return tc1_temp_.get(); }
    inline const int32_t& get_tc1_temp() const { return tc1_temp_.get(); }
    inline int32_t tc1_temp() const { return tc1_temp_.get(); }

    static constexpr char const* TC2_TEMP_NAME = "tc2_temp";
    inline void clear_tc2_temp() { tc2_temp_.clear(); }
    inline void set_tc2_temp(const int32_t& value) { tc2_temp_ = value; }
    inline void set_tc2_temp(const int32_t&& value) { tc2_temp_ = value; }
    inline int32_t& mutable_tc2_temp() { return tc2_temp_.get(); }
    inline const int32_t& get_tc2_temp() const { return tc2_temp_.get(); }
    inline int32_t tc2_temp() const { return tc2_temp_.get(); }


    ::EmbeddedProto::Error serialize(::EmbeddedProto::WriteBufferInterface& buffer) const override
    {
      ::EmbeddedProto::Error return_value = ::EmbeddedProto::Error::NO_ERRORS;

      if((0 != tc1_temp_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = tc1_temp_.serialize_with_id(static_cast<uint32_t>(FieldNumber::TC1_TEMP), buffer, false);
      }

      if((0 != tc2_temp_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = tc2_temp_.serialize_with_id(static_cast<uint32_t>(FieldNumber::TC2_TEMP), buffer, false);
      }

      return return_value;
    };

    ::EmbeddedProto::Error deserialize(::EmbeddedProto::ReadBufferInterface& buffer) override
    {
      ::EmbeddedProto::Error return_value = ::EmbeddedProto::Error::NO_ERRORS;
      ::EmbeddedProto::WireFormatter::WireType wire_type = ::EmbeddedProto::WireFormatter::WireType::VARINT;
      uint32_t id_number = 0;
      FieldNumber id_tag = FieldNumber::NOT_SET;

      ::EmbeddedProto::Error tag_value = ::EmbeddedProto::WireFormatter::DeserializeTag(buffer, wire_type, id_number);
      while((::EmbeddedProto::Error::NO_ERRORS == return_value) && (::EmbeddedProto::Error::NO_ERRORS == tag_value))
      {
        id_tag = static_cast<FieldNumber>(id_number);
        switch(id_tag)
        {
          case FieldNumber::TC1_TEMP:
            return_value = tc1_temp_.deserialize_check_type(buffer, wire_type);
            break;

          case FieldNumber::TC2_TEMP:
            return_value = tc2_temp_.deserialize_check_type(buffer, wire_type);
            break;

          case FieldNumber::NOT_SET:
            return_value = ::EmbeddedProto::Error::INVALID_FIELD_ID;
            break;

          default:
            return_value = skip_unknown_field(buffer, wire_type);
            break;
        }

        if(::EmbeddedProto::Error::NO_ERRORS == return_value)
        {
          // Read the next tag.
          tag_value = ::EmbeddedProto::WireFormatter::DeserializeTag(buffer, wire_type, id_number);
        }
      }

      // When an error was detect while reading the tag but no other errors where found, set it in the return value.
      if((::EmbeddedProto::Error::NO_ERRORS == return_value)
         && (::EmbeddedProto::Error::NO_ERRORS != tag_value)
         && (::EmbeddedProto::Error::END_OF_BUFFER != tag_value)) // The end of the buffer is not an array in this case.
      {
        return_value = tag_value;
      }

      return return_value;
    };

    void clear() override
    {
      clear_tc1_temp();
      clear_tc2_temp();

    }

    static char const* field_number_to_name(const FieldNumber fieldNumber)
    {
      char const* name = nullptr;
      switch(fieldNumber)
      {
        case FieldNumber::TC1_TEMP:
          name = TC1_TEMP_NAME;
          break;
        case FieldNumber::TC2_TEMP:
          name = TC2_TEMP_NAME;
          break;
        default:
          name = "Invalid FieldNumber";
          break;
      }
      return name;
    }

#ifdef MSG_TO_STRING

    ::EmbeddedProto::string_view to_string(::EmbeddedProto::string_view& str) const
    {
      return this->to_string(str, 0, nullptr, true);
    }

    ::EmbeddedProto::string_view to_string(::EmbeddedProto::string_view& str, const uint32_t indent_level, char const* name, const bool first_field) const override
    {
      ::EmbeddedProto::string_view left_chars = str;
      int32_t n_chars_used = 0;

      if(!first_field)
      {
        // Add a comma behind the previous field.
        n_chars_used = snprintf(left_chars.data, left_chars.size, ",\n");
        if(0 < n_chars_used)
        {
          // Update the character pointer and characters left in the array.
          left_chars.data += n_chars_used;
          left_chars.size -= n_chars_used;
        }
      }

      if(nullptr != name)
      {
        if( 0 == indent_level)
        {
          n_chars_used = snprintf(left_chars.data, left_chars.size, "\"%s\": {\n", name);
        }
        else
        {
          n_chars_used = snprintf(left_chars.data, left_chars.size, "%*s\"%s\": {\n", indent_level, " ", name);
        }
      }
      else
      {
        if( 0 == indent_level)
        {
          n_chars_used = snprintf(left_chars.data, left_chars.size, "{\n");
        }
        else
        {
          n_chars_used = snprintf(left_chars.data, left_chars.size, "%*s{\n", indent_level, " ");
        }
      }
      
      if(0 < n_chars_used)
      {
        left_chars.data += n_chars_used;
        left_chars.size -= n_chars_used;
      }

      left_chars = tc1_temp_.to_string(left_chars, indent_level + 2, TC1_TEMP_NAME, true);
      left_chars = tc2_temp_.to_string(left_chars, indent_level + 2, TC2_TEMP_NAME, false);
  
      if( 0 == indent_level) 
      {
        n_chars_used = snprintf(left_chars.data, left_chars.size, "\n}");
      }
      else 
      {
        n_chars_used = snprintf(left_chars.data, left_chars.size, "\n%*s}", indent_level, " ");
      }

      if(0 < n_chars_used)
      {
        left_chars.data += n_chars_used;
        left_chars.size -= n_chars_used;
      }

      return left_chars;
    }

#endif // End of MSG_TO_STRING

  private:


      EmbeddedProto::int32 tc1_temp_ = 0;
      EmbeddedProto::int32 tc2_temp_ = 0;

};

class RelayStatus final: public ::EmbeddedProto::MessageInterface
{
  public:
    RelayStatus() = default;
    RelayStatus(const RelayStatus& rhs )
    {
      set_ac1_open(rhs.get_ac1_open());
      set_ac2_open(rhs.get_ac2_open());
      set_pbv1_open(rhs.get_pbv1_open());
      set_pbv2_open(rhs.get_pbv2_open());
      set_pbv3_open(rhs.get_pbv3_open());
      set_sol1_open(rhs.get_sol1_open());
      set_sol2_open(rhs.get_sol2_open());
      set_sol3_open(rhs.get_sol3_open());
      set_sol4_open(rhs.get_sol4_open());
      set_sol5_open(rhs.get_sol5_open());
      set_sol6_open(rhs.get_sol6_open());
      set_sol7_open(rhs.get_sol7_open());
      set_sol8a_open(rhs.get_sol8a_open());
      set_sol8b_open(rhs.get_sol8b_open());
    }

    RelayStatus(const RelayStatus&& rhs ) noexcept
    {
      set_ac1_open(rhs.get_ac1_open());
      set_ac2_open(rhs.get_ac2_open());
      set_pbv1_open(rhs.get_pbv1_open());
      set_pbv2_open(rhs.get_pbv2_open());
      set_pbv3_open(rhs.get_pbv3_open());
      set_sol1_open(rhs.get_sol1_open());
      set_sol2_open(rhs.get_sol2_open());
      set_sol3_open(rhs.get_sol3_open());
      set_sol4_open(rhs.get_sol4_open());
      set_sol5_open(rhs.get_sol5_open());
      set_sol6_open(rhs.get_sol6_open());
      set_sol7_open(rhs.get_sol7_open());
      set_sol8a_open(rhs.get_sol8a_open());
      set_sol8b_open(rhs.get_sol8b_open());
    }

    ~RelayStatus() override = default;

    enum class FieldNumber : uint32_t
    {
      NOT_SET = 0,
      AC1_OPEN = 1,
      AC2_OPEN = 2,
      PBV1_OPEN = 3,
      PBV2_OPEN = 4,
      PBV3_OPEN = 5,
      SOL1_OPEN = 6,
      SOL2_OPEN = 7,
      SOL3_OPEN = 8,
      SOL4_OPEN = 9,
      SOL5_OPEN = 10,
      SOL6_OPEN = 11,
      SOL7_OPEN = 12,
      SOL8A_OPEN = 13,
      SOL8B_OPEN = 14
    };

    RelayStatus& operator=(const RelayStatus& rhs)
    {
      set_ac1_open(rhs.get_ac1_open());
      set_ac2_open(rhs.get_ac2_open());
      set_pbv1_open(rhs.get_pbv1_open());
      set_pbv2_open(rhs.get_pbv2_open());
      set_pbv3_open(rhs.get_pbv3_open());
      set_sol1_open(rhs.get_sol1_open());
      set_sol2_open(rhs.get_sol2_open());
      set_sol3_open(rhs.get_sol3_open());
      set_sol4_open(rhs.get_sol4_open());
      set_sol5_open(rhs.get_sol5_open());
      set_sol6_open(rhs.get_sol6_open());
      set_sol7_open(rhs.get_sol7_open());
      set_sol8a_open(rhs.get_sol8a_open());
      set_sol8b_open(rhs.get_sol8b_open());
      return *this;
    }

    RelayStatus& operator=(const RelayStatus&& rhs) noexcept
    {
      set_ac1_open(rhs.get_ac1_open());
      set_ac2_open(rhs.get_ac2_open());
      set_pbv1_open(rhs.get_pbv1_open());
      set_pbv2_open(rhs.get_pbv2_open());
      set_pbv3_open(rhs.get_pbv3_open());
      set_sol1_open(rhs.get_sol1_open());
      set_sol2_open(rhs.get_sol2_open());
      set_sol3_open(rhs.get_sol3_open());
      set_sol4_open(rhs.get_sol4_open());
      set_sol5_open(rhs.get_sol5_open());
      set_sol6_open(rhs.get_sol6_open());
      set_sol7_open(rhs.get_sol7_open());
      set_sol8a_open(rhs.get_sol8a_open());
      set_sol8b_open(rhs.get_sol8b_open());
      return *this;
    }

    static constexpr char const* AC1_OPEN_NAME = "ac1_open";
    inline void clear_ac1_open() { ac1_open_.clear(); }
    inline void set_ac1_open(const bool& value) { ac1_open_ = value; }
    inline void set_ac1_open(const bool&& value) { ac1_open_ = value; }
    inline bool& mutable_ac1_open() { return ac1_open_.get(); }
    inline const bool& get_ac1_open() const { return ac1_open_.get(); }
    inline bool ac1_open() const { return ac1_open_.get(); }

    static constexpr char const* AC2_OPEN_NAME = "ac2_open";
    inline void clear_ac2_open() { ac2_open_.clear(); }
    inline void set_ac2_open(const bool& value) { ac2_open_ = value; }
    inline void set_ac2_open(const bool&& value) { ac2_open_ = value; }
    inline bool& mutable_ac2_open() { return ac2_open_.get(); }
    inline const bool& get_ac2_open() const { return ac2_open_.get(); }
    inline bool ac2_open() const { return ac2_open_.get(); }

    static constexpr char const* PBV1_OPEN_NAME = "pbv1_open";
    inline void clear_pbv1_open() { pbv1_open_.clear(); }
    inline void set_pbv1_open(const bool& value) { pbv1_open_ = value; }
    inline void set_pbv1_open(const bool&& value) { pbv1_open_ = value; }
    inline bool& mutable_pbv1_open() { return pbv1_open_.get(); }
    inline const bool& get_pbv1_open() const { return pbv1_open_.get(); }
    inline bool pbv1_open() const { return pbv1_open_.get(); }

    static constexpr char const* PBV2_OPEN_NAME = "pbv2_open";
    inline void clear_pbv2_open() { pbv2_open_.clear(); }
    inline void set_pbv2_open(const bool& value) { pbv2_open_ = value; }
    inline void set_pbv2_open(const bool&& value) { pbv2_open_ = value; }
    inline bool& mutable_pbv2_open() { return pbv2_open_.get(); }
    inline const bool& get_pbv2_open() const { return pbv2_open_.get(); }
    inline bool pbv2_open() const { return pbv2_open_.get(); }

    static constexpr char const* PBV3_OPEN_NAME = "pbv3_open";
    inline void clear_pbv3_open() { pbv3_open_.clear(); }
    inline void set_pbv3_open(const bool& value) { pbv3_open_ = value; }
    inline void set_pbv3_open(const bool&& value) { pbv3_open_ = value; }
    inline bool& mutable_pbv3_open() { return pbv3_open_.get(); }
    inline const bool& get_pbv3_open() const { return pbv3_open_.get(); }
    inline bool pbv3_open() const { return pbv3_open_.get(); }

    static constexpr char const* SOL1_OPEN_NAME = "sol1_open";
    inline void clear_sol1_open() { sol1_open_.clear(); }
    inline void set_sol1_open(const bool& value) { sol1_open_ = value; }
    inline void set_sol1_open(const bool&& value) { sol1_open_ = value; }
    inline bool& mutable_sol1_open() { return sol1_open_.get(); }
    inline const bool& get_sol1_open() const { return sol1_open_.get(); }
    inline bool sol1_open() const { return sol1_open_.get(); }

    static constexpr char const* SOL2_OPEN_NAME = "sol2_open";
    inline void clear_sol2_open() { sol2_open_.clear(); }
    inline void set_sol2_open(const bool& value) { sol2_open_ = value; }
    inline void set_sol2_open(const bool&& value) { sol2_open_ = value; }
    inline bool& mutable_sol2_open() { return sol2_open_.get(); }
    inline const bool& get_sol2_open() const { return sol2_open_.get(); }
    inline bool sol2_open() const { return sol2_open_.get(); }

    static constexpr char const* SOL3_OPEN_NAME = "sol3_open";
    inline void clear_sol3_open() { sol3_open_.clear(); }
    inline void set_sol3_open(const bool& value) { sol3_open_ = value; }
    inline void set_sol3_open(const bool&& value) { sol3_open_ = value; }
    inline bool& mutable_sol3_open() { return sol3_open_.get(); }
    inline const bool& get_sol3_open() const { return sol3_open_.get(); }
    inline bool sol3_open() const { return sol3_open_.get(); }

    static constexpr char const* SOL4_OPEN_NAME = "sol4_open";
    inline void clear_sol4_open() { sol4_open_.clear(); }
    inline void set_sol4_open(const bool& value) { sol4_open_ = value; }
    inline void set_sol4_open(const bool&& value) { sol4_open_ = value; }
    inline bool& mutable_sol4_open() { return sol4_open_.get(); }
    inline const bool& get_sol4_open() const { return sol4_open_.get(); }
    inline bool sol4_open() const { return sol4_open_.get(); }

    static constexpr char const* SOL5_OPEN_NAME = "sol5_open";
    inline void clear_sol5_open() { sol5_open_.clear(); }
    inline void set_sol5_open(const bool& value) { sol5_open_ = value; }
    inline void set_sol5_open(const bool&& value) { sol5_open_ = value; }
    inline bool& mutable_sol5_open() { return sol5_open_.get(); }
    inline const bool& get_sol5_open() const { return sol5_open_.get(); }
    inline bool sol5_open() const { return sol5_open_.get(); }

    static constexpr char const* SOL6_OPEN_NAME = "sol6_open";
    inline void clear_sol6_open() { sol6_open_.clear(); }
    inline void set_sol6_open(const bool& value) { sol6_open_ = value; }
    inline void set_sol6_open(const bool&& value) { sol6_open_ = value; }
    inline bool& mutable_sol6_open() { return sol6_open_.get(); }
    inline const bool& get_sol6_open() const { return sol6_open_.get(); }
    inline bool sol6_open() const { return sol6_open_.get(); }

    static constexpr char const* SOL7_OPEN_NAME = "sol7_open";
    inline void clear_sol7_open() { sol7_open_.clear(); }
    inline void set_sol7_open(const bool& value) { sol7_open_ = value; }
    inline void set_sol7_open(const bool&& value) { sol7_open_ = value; }
    inline bool& mutable_sol7_open() { return sol7_open_.get(); }
    inline const bool& get_sol7_open() const { return sol7_open_.get(); }
    inline bool sol7_open() const { return sol7_open_.get(); }

    static constexpr char const* SOL8A_OPEN_NAME = "sol8a_open";
    inline void clear_sol8a_open() { sol8a_open_.clear(); }
    inline void set_sol8a_open(const bool& value) { sol8a_open_ = value; }
    inline void set_sol8a_open(const bool&& value) { sol8a_open_ = value; }
    inline bool& mutable_sol8a_open() { return sol8a_open_.get(); }
    inline const bool& get_sol8a_open() const { return sol8a_open_.get(); }
    inline bool sol8a_open() const { return sol8a_open_.get(); }

    static constexpr char const* SOL8B_OPEN_NAME = "sol8b_open";
    inline void clear_sol8b_open() { sol8b_open_.clear(); }
    inline void set_sol8b_open(const bool& value) { sol8b_open_ = value; }
    inline void set_sol8b_open(const bool&& value) { sol8b_open_ = value; }
    inline bool& mutable_sol8b_open() { return sol8b_open_.get(); }
    inline const bool& get_sol8b_open() const { return sol8b_open_.get(); }
    inline bool sol8b_open() const { return sol8b_open_.get(); }


    ::EmbeddedProto::Error serialize(::EmbeddedProto::WriteBufferInterface& buffer) const override
    {
      ::EmbeddedProto::Error return_value = ::EmbeddedProto::Error::NO_ERRORS;

      if((false != ac1_open_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = ac1_open_.serialize_with_id(static_cast<uint32_t>(FieldNumber::AC1_OPEN), buffer, false);
      }

      if((false != ac2_open_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = ac2_open_.serialize_with_id(static_cast<uint32_t>(FieldNumber::AC2_OPEN), buffer, false);
      }

      if((false != pbv1_open_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = pbv1_open_.serialize_with_id(static_cast<uint32_t>(FieldNumber::PBV1_OPEN), buffer, false);
      }

      if((false != pbv2_open_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = pbv2_open_.serialize_with_id(static_cast<uint32_t>(FieldNumber::PBV2_OPEN), buffer, false);
      }

      if((false != pbv3_open_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = pbv3_open_.serialize_with_id(static_cast<uint32_t>(FieldNumber::PBV3_OPEN), buffer, false);
      }

      if((false != sol1_open_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = sol1_open_.serialize_with_id(static_cast<uint32_t>(FieldNumber::SOL1_OPEN), buffer, false);
      }

      if((false != sol2_open_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = sol2_open_.serialize_with_id(static_cast<uint32_t>(FieldNumber::SOL2_OPEN), buffer, false);
      }

      if((false != sol3_open_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = sol3_open_.serialize_with_id(static_cast<uint32_t>(FieldNumber::SOL3_OPEN), buffer, false);
      }

      if((false != sol4_open_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = sol4_open_.serialize_with_id(static_cast<uint32_t>(FieldNumber::SOL4_OPEN), buffer, false);
      }

      if((false != sol5_open_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = sol5_open_.serialize_with_id(static_cast<uint32_t>(FieldNumber::SOL5_OPEN), buffer, false);
      }

      if((false != sol6_open_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = sol6_open_.serialize_with_id(static_cast<uint32_t>(FieldNumber::SOL6_OPEN), buffer, false);
      }

      if((false != sol7_open_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = sol7_open_.serialize_with_id(static_cast<uint32_t>(FieldNumber::SOL7_OPEN), buffer, false);
      }

      if((false != sol8a_open_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = sol8a_open_.serialize_with_id(static_cast<uint32_t>(FieldNumber::SOL8A_OPEN), buffer, false);
      }

      if((false != sol8b_open_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = sol8b_open_.serialize_with_id(static_cast<uint32_t>(FieldNumber::SOL8B_OPEN), buffer, false);
      }

      return return_value;
    };

    ::EmbeddedProto::Error deserialize(::EmbeddedProto::ReadBufferInterface& buffer) override
    {
      ::EmbeddedProto::Error return_value = ::EmbeddedProto::Error::NO_ERRORS;
      ::EmbeddedProto::WireFormatter::WireType wire_type = ::EmbeddedProto::WireFormatter::WireType::VARINT;
      uint32_t id_number = 0;
      FieldNumber id_tag = FieldNumber::NOT_SET;

      ::EmbeddedProto::Error tag_value = ::EmbeddedProto::WireFormatter::DeserializeTag(buffer, wire_type, id_number);
      while((::EmbeddedProto::Error::NO_ERRORS == return_value) && (::EmbeddedProto::Error::NO_ERRORS == tag_value))
      {
        id_tag = static_cast<FieldNumber>(id_number);
        switch(id_tag)
        {
          case FieldNumber::AC1_OPEN:
            return_value = ac1_open_.deserialize_check_type(buffer, wire_type);
            break;

          case FieldNumber::AC2_OPEN:
            return_value = ac2_open_.deserialize_check_type(buffer, wire_type);
            break;

          case FieldNumber::PBV1_OPEN:
            return_value = pbv1_open_.deserialize_check_type(buffer, wire_type);
            break;

          case FieldNumber::PBV2_OPEN:
            return_value = pbv2_open_.deserialize_check_type(buffer, wire_type);
            break;

          case FieldNumber::PBV3_OPEN:
            return_value = pbv3_open_.deserialize_check_type(buffer, wire_type);
            break;

          case FieldNumber::SOL1_OPEN:
            return_value = sol1_open_.deserialize_check_type(buffer, wire_type);
            break;

          case FieldNumber::SOL2_OPEN:
            return_value = sol2_open_.deserialize_check_type(buffer, wire_type);
            break;

          case FieldNumber::SOL3_OPEN:
            return_value = sol3_open_.deserialize_check_type(buffer, wire_type);
            break;

          case FieldNumber::SOL4_OPEN:
            return_value = sol4_open_.deserialize_check_type(buffer, wire_type);
            break;

          case FieldNumber::SOL5_OPEN:
            return_value = sol5_open_.deserialize_check_type(buffer, wire_type);
            break;

          case FieldNumber::SOL6_OPEN:
            return_value = sol6_open_.deserialize_check_type(buffer, wire_type);
            break;

          case FieldNumber::SOL7_OPEN:
            return_value = sol7_open_.deserialize_check_type(buffer, wire_type);
            break;

          case FieldNumber::SOL8A_OPEN:
            return_value = sol8a_open_.deserialize_check_type(buffer, wire_type);
            break;

          case FieldNumber::SOL8B_OPEN:
            return_value = sol8b_open_.deserialize_check_type(buffer, wire_type);
            break;

          case FieldNumber::NOT_SET:
            return_value = ::EmbeddedProto::Error::INVALID_FIELD_ID;
            break;

          default:
            return_value = skip_unknown_field(buffer, wire_type);
            break;
        }

        if(::EmbeddedProto::Error::NO_ERRORS == return_value)
        {
          // Read the next tag.
          tag_value = ::EmbeddedProto::WireFormatter::DeserializeTag(buffer, wire_type, id_number);
        }
      }

      // When an error was detect while reading the tag but no other errors where found, set it in the return value.
      if((::EmbeddedProto::Error::NO_ERRORS == return_value)
         && (::EmbeddedProto::Error::NO_ERRORS != tag_value)
         && (::EmbeddedProto::Error::END_OF_BUFFER != tag_value)) // The end of the buffer is not an array in this case.
      {
        return_value = tag_value;
      }

      return return_value;
    };

    void clear() override
    {
      clear_ac1_open();
      clear_ac2_open();
      clear_pbv1_open();
      clear_pbv2_open();
      clear_pbv3_open();
      clear_sol1_open();
      clear_sol2_open();
      clear_sol3_open();
      clear_sol4_open();
      clear_sol5_open();
      clear_sol6_open();
      clear_sol7_open();
      clear_sol8a_open();
      clear_sol8b_open();

    }

    static char const* field_number_to_name(const FieldNumber fieldNumber)
    {
      char const* name = nullptr;
      switch(fieldNumber)
      {
        case FieldNumber::AC1_OPEN:
          name = AC1_OPEN_NAME;
          break;
        case FieldNumber::AC2_OPEN:
          name = AC2_OPEN_NAME;
          break;
        case FieldNumber::PBV1_OPEN:
          name = PBV1_OPEN_NAME;
          break;
        case FieldNumber::PBV2_OPEN:
          name = PBV2_OPEN_NAME;
          break;
        case FieldNumber::PBV3_OPEN:
          name = PBV3_OPEN_NAME;
          break;
        case FieldNumber::SOL1_OPEN:
          name = SOL1_OPEN_NAME;
          break;
        case FieldNumber::SOL2_OPEN:
          name = SOL2_OPEN_NAME;
          break;
        case FieldNumber::SOL3_OPEN:
          name = SOL3_OPEN_NAME;
          break;
        case FieldNumber::SOL4_OPEN:
          name = SOL4_OPEN_NAME;
          break;
        case FieldNumber::SOL5_OPEN:
          name = SOL5_OPEN_NAME;
          break;
        case FieldNumber::SOL6_OPEN:
          name = SOL6_OPEN_NAME;
          break;
        case FieldNumber::SOL7_OPEN:
          name = SOL7_OPEN_NAME;
          break;
        case FieldNumber::SOL8A_OPEN:
          name = SOL8A_OPEN_NAME;
          break;
        case FieldNumber::SOL8B_OPEN:
          name = SOL8B_OPEN_NAME;
          break;
        default:
          name = "Invalid FieldNumber";
          break;
      }
      return name;
    }

#ifdef MSG_TO_STRING

    ::EmbeddedProto::string_view to_string(::EmbeddedProto::string_view& str) const
    {
      return this->to_string(str, 0, nullptr, true);
    }

    ::EmbeddedProto::string_view to_string(::EmbeddedProto::string_view& str, const uint32_t indent_level, char const* name, const bool first_field) const override
    {
      ::EmbeddedProto::string_view left_chars = str;
      int32_t n_chars_used = 0;

      if(!first_field)
      {
        // Add a comma behind the previous field.
        n_chars_used = snprintf(left_chars.data, left_chars.size, ",\n");
        if(0 < n_chars_used)
        {
          // Update the character pointer and characters left in the array.
          left_chars.data += n_chars_used;
          left_chars.size -= n_chars_used;
        }
      }

      if(nullptr != name)
      {
        if( 0 == indent_level)
        {
          n_chars_used = snprintf(left_chars.data, left_chars.size, "\"%s\": {\n", name);
        }
        else
        {
          n_chars_used = snprintf(left_chars.data, left_chars.size, "%*s\"%s\": {\n", indent_level, " ", name);
        }
      }
      else
      {
        if( 0 == indent_level)
        {
          n_chars_used = snprintf(left_chars.data, left_chars.size, "{\n");
        }
        else
        {
          n_chars_used = snprintf(left_chars.data, left_chars.size, "%*s{\n", indent_level, " ");
        }
      }
      
      if(0 < n_chars_used)
      {
        left_chars.data += n_chars_used;
        left_chars.size -= n_chars_used;
      }

      left_chars = ac1_open_.to_string(left_chars, indent_level + 2, AC1_OPEN_NAME, true);
      left_chars = ac2_open_.to_string(left_chars, indent_level + 2, AC2_OPEN_NAME, false);
      left_chars = pbv1_open_.to_string(left_chars, indent_level + 2, PBV1_OPEN_NAME, false);
      left_chars = pbv2_open_.to_string(left_chars, indent_level + 2, PBV2_OPEN_NAME, false);
      left_chars = pbv3_open_.to_string(left_chars, indent_level + 2, PBV3_OPEN_NAME, false);
      left_chars = sol1_open_.to_string(left_chars, indent_level + 2, SOL1_OPEN_NAME, false);
      left_chars = sol2_open_.to_string(left_chars, indent_level + 2, SOL2_OPEN_NAME, false);
      left_chars = sol3_open_.to_string(left_chars, indent_level + 2, SOL3_OPEN_NAME, false);
      left_chars = sol4_open_.to_string(left_chars, indent_level + 2, SOL4_OPEN_NAME, false);
      left_chars = sol5_open_.to_string(left_chars, indent_level + 2, SOL5_OPEN_NAME, false);
      left_chars = sol6_open_.to_string(left_chars, indent_level + 2, SOL6_OPEN_NAME, false);
      left_chars = sol7_open_.to_string(left_chars, indent_level + 2, SOL7_OPEN_NAME, false);
      left_chars = sol8a_open_.to_string(left_chars, indent_level + 2, SOL8A_OPEN_NAME, false);
      left_chars = sol8b_open_.to_string(left_chars, indent_level + 2, SOL8B_OPEN_NAME, false);
  
      if( 0 == indent_level) 
      {
        n_chars_used = snprintf(left_chars.data, left_chars.size, "\n}");
      }
      else 
      {
        n_chars_used = snprintf(left_chars.data, left_chars.size, "\n%*s}", indent_level, " ");
      }

      if(0 < n_chars_used)
      {
        left_chars.data += n_chars_used;
        left_chars.size -= n_chars_used;
      }

      return left_chars;
    }

#endif // End of MSG_TO_STRING

  private:


      EmbeddedProto::boolean ac1_open_ = false;
      EmbeddedProto::boolean ac2_open_ = false;
      EmbeddedProto::boolean pbv1_open_ = false;
      EmbeddedProto::boolean pbv2_open_ = false;
      EmbeddedProto::boolean pbv3_open_ = false;
      EmbeddedProto::boolean sol1_open_ = false;
      EmbeddedProto::boolean sol2_open_ = false;
      EmbeddedProto::boolean sol3_open_ = false;
      EmbeddedProto::boolean sol4_open_ = false;
      EmbeddedProto::boolean sol5_open_ = false;
      EmbeddedProto::boolean sol6_open_ = false;
      EmbeddedProto::boolean sol7_open_ = false;
      EmbeddedProto::boolean sol8a_open_ = false;
      EmbeddedProto::boolean sol8b_open_ = false;

};

class SOBTemp final: public ::EmbeddedProto::MessageInterface
{
  public:
    SOBTemp() = default;
    SOBTemp(const SOBTemp& rhs )
    {
      set_tc1_temp(rhs.get_tc1_temp());
      set_tc2_temp(rhs.get_tc2_temp());
    }

    SOBTemp(const SOBTemp&& rhs ) noexcept
    {
      set_tc1_temp(rhs.get_tc1_temp());
      set_tc2_temp(rhs.get_tc2_temp());
    }

    ~SOBTemp() override = default;

    enum class FieldNumber : uint32_t
    {
      NOT_SET = 0,
      TC1_TEMP = 1,
      TC2_TEMP = 2
    };

    SOBTemp& operator=(const SOBTemp& rhs)
    {
      set_tc1_temp(rhs.get_tc1_temp());
      set_tc2_temp(rhs.get_tc2_temp());
      return *this;
    }

    SOBTemp& operator=(const SOBTemp&& rhs) noexcept
    {
      set_tc1_temp(rhs.get_tc1_temp());
      set_tc2_temp(rhs.get_tc2_temp());
      return *this;
    }

    static constexpr char const* TC1_TEMP_NAME = "tc1_temp";
    inline void clear_tc1_temp() { tc1_temp_.clear(); }
    inline void set_tc1_temp(const int32_t& value) { tc1_temp_ = value; }
    inline void set_tc1_temp(const int32_t&& value) { tc1_temp_ = value; }
    inline int32_t& mutable_tc1_temp() { return tc1_temp_.get(); }
    inline const int32_t& get_tc1_temp() const { return tc1_temp_.get(); }
    inline int32_t tc1_temp() const { return tc1_temp_.get(); }

    static constexpr char const* TC2_TEMP_NAME = "tc2_temp";
    inline void clear_tc2_temp() { tc2_temp_.clear(); }
    inline void set_tc2_temp(const int32_t& value) { tc2_temp_ = value; }
    inline void set_tc2_temp(const int32_t&& value) { tc2_temp_ = value; }
    inline int32_t& mutable_tc2_temp() { return tc2_temp_.get(); }
    inline const int32_t& get_tc2_temp() const { return tc2_temp_.get(); }
    inline int32_t tc2_temp() const { return tc2_temp_.get(); }


    ::EmbeddedProto::Error serialize(::EmbeddedProto::WriteBufferInterface& buffer) const override
    {
      ::EmbeddedProto::Error return_value = ::EmbeddedProto::Error::NO_ERRORS;

      if((0 != tc1_temp_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = tc1_temp_.serialize_with_id(static_cast<uint32_t>(FieldNumber::TC1_TEMP), buffer, false);
      }

      if((0 != tc2_temp_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = tc2_temp_.serialize_with_id(static_cast<uint32_t>(FieldNumber::TC2_TEMP), buffer, false);
      }

      return return_value;
    };

    ::EmbeddedProto::Error deserialize(::EmbeddedProto::ReadBufferInterface& buffer) override
    {
      ::EmbeddedProto::Error return_value = ::EmbeddedProto::Error::NO_ERRORS;
      ::EmbeddedProto::WireFormatter::WireType wire_type = ::EmbeddedProto::WireFormatter::WireType::VARINT;
      uint32_t id_number = 0;
      FieldNumber id_tag = FieldNumber::NOT_SET;

      ::EmbeddedProto::Error tag_value = ::EmbeddedProto::WireFormatter::DeserializeTag(buffer, wire_type, id_number);
      while((::EmbeddedProto::Error::NO_ERRORS == return_value) && (::EmbeddedProto::Error::NO_ERRORS == tag_value))
      {
        id_tag = static_cast<FieldNumber>(id_number);
        switch(id_tag)
        {
          case FieldNumber::TC1_TEMP:
            return_value = tc1_temp_.deserialize_check_type(buffer, wire_type);
            break;

          case FieldNumber::TC2_TEMP:
            return_value = tc2_temp_.deserialize_check_type(buffer, wire_type);
            break;

          case FieldNumber::NOT_SET:
            return_value = ::EmbeddedProto::Error::INVALID_FIELD_ID;
            break;

          default:
            return_value = skip_unknown_field(buffer, wire_type);
            break;
        }

        if(::EmbeddedProto::Error::NO_ERRORS == return_value)
        {
          // Read the next tag.
          tag_value = ::EmbeddedProto::WireFormatter::DeserializeTag(buffer, wire_type, id_number);
        }
      }

      // When an error was detect while reading the tag but no other errors where found, set it in the return value.
      if((::EmbeddedProto::Error::NO_ERRORS == return_value)
         && (::EmbeddedProto::Error::NO_ERRORS != tag_value)
         && (::EmbeddedProto::Error::END_OF_BUFFER != tag_value)) // The end of the buffer is not an array in this case.
      {
        return_value = tag_value;
      }

      return return_value;
    };

    void clear() override
    {
      clear_tc1_temp();
      clear_tc2_temp();

    }

    static char const* field_number_to_name(const FieldNumber fieldNumber)
    {
      char const* name = nullptr;
      switch(fieldNumber)
      {
        case FieldNumber::TC1_TEMP:
          name = TC1_TEMP_NAME;
          break;
        case FieldNumber::TC2_TEMP:
          name = TC2_TEMP_NAME;
          break;
        default:
          name = "Invalid FieldNumber";
          break;
      }
      return name;
    }

#ifdef MSG_TO_STRING

    ::EmbeddedProto::string_view to_string(::EmbeddedProto::string_view& str) const
    {
      return this->to_string(str, 0, nullptr, true);
    }

    ::EmbeddedProto::string_view to_string(::EmbeddedProto::string_view& str, const uint32_t indent_level, char const* name, const bool first_field) const override
    {
      ::EmbeddedProto::string_view left_chars = str;
      int32_t n_chars_used = 0;

      if(!first_field)
      {
        // Add a comma behind the previous field.
        n_chars_used = snprintf(left_chars.data, left_chars.size, ",\n");
        if(0 < n_chars_used)
        {
          // Update the character pointer and characters left in the array.
          left_chars.data += n_chars_used;
          left_chars.size -= n_chars_used;
        }
      }

      if(nullptr != name)
      {
        if( 0 == indent_level)
        {
          n_chars_used = snprintf(left_chars.data, left_chars.size, "\"%s\": {\n", name);
        }
        else
        {
          n_chars_used = snprintf(left_chars.data, left_chars.size, "%*s\"%s\": {\n", indent_level, " ", name);
        }
      }
      else
      {
        if( 0 == indent_level)
        {
          n_chars_used = snprintf(left_chars.data, left_chars.size, "{\n");
        }
        else
        {
          n_chars_used = snprintf(left_chars.data, left_chars.size, "%*s{\n", indent_level, " ");
        }
      }
      
      if(0 < n_chars_used)
      {
        left_chars.data += n_chars_used;
        left_chars.size -= n_chars_used;
      }

      left_chars = tc1_temp_.to_string(left_chars, indent_level + 2, TC1_TEMP_NAME, true);
      left_chars = tc2_temp_.to_string(left_chars, indent_level + 2, TC2_TEMP_NAME, false);
  
      if( 0 == indent_level) 
      {
        n_chars_used = snprintf(left_chars.data, left_chars.size, "\n}");
      }
      else 
      {
        n_chars_used = snprintf(left_chars.data, left_chars.size, "\n%*s}", indent_level, " ");
      }

      if(0 < n_chars_used)
      {
        left_chars.data += n_chars_used;
        left_chars.size -= n_chars_used;
      }

      return left_chars;
    }

#endif // End of MSG_TO_STRING

  private:


      EmbeddedProto::int32 tc1_temp_ = 0;
      EmbeddedProto::int32 tc2_temp_ = 0;

};

class GPS final: public ::EmbeddedProto::MessageInterface
{
  public:
    GPS() = default;
    GPS(const GPS& rhs )
    {
      set_latitude(rhs.get_latitude());
      set_longitude(rhs.get_longitude());
      set_antenna_alt(rhs.get_antenna_alt());
      set_geoidAltitude(rhs.get_geoidAltitude());
      set_total_alt(rhs.get_total_alt());
      set_time(rhs.get_time());
    }

    GPS(const GPS&& rhs ) noexcept
    {
      set_latitude(rhs.get_latitude());
      set_longitude(rhs.get_longitude());
      set_antenna_alt(rhs.get_antenna_alt());
      set_geoidAltitude(rhs.get_geoidAltitude());
      set_total_alt(rhs.get_total_alt());
      set_time(rhs.get_time());
    }

    ~GPS() override = default;

    enum class FieldNumber : uint32_t
    {
      NOT_SET = 0,
      LATITUDE = 1,
      LONGITUDE = 2,
      ANTENNA_ALT = 3,
      GEOIDALTITUDE = 4,
      TOTAL_ALT = 5,
      TIME = 6
    };

    GPS& operator=(const GPS& rhs)
    {
      set_latitude(rhs.get_latitude());
      set_longitude(rhs.get_longitude());
      set_antenna_alt(rhs.get_antenna_alt());
      set_geoidAltitude(rhs.get_geoidAltitude());
      set_total_alt(rhs.get_total_alt());
      set_time(rhs.get_time());
      return *this;
    }

    GPS& operator=(const GPS&& rhs) noexcept
    {
      set_latitude(rhs.get_latitude());
      set_longitude(rhs.get_longitude());
      set_antenna_alt(rhs.get_antenna_alt());
      set_geoidAltitude(rhs.get_geoidAltitude());
      set_total_alt(rhs.get_total_alt());
      set_time(rhs.get_time());
      return *this;
    }

    static constexpr char const* LATITUDE_NAME = "latitude";
    inline void clear_latitude() { latitude_.clear(); }
    inline void set_latitude(const LatLong& value) { latitude_ = value; }
    inline void set_latitude(const LatLong&& value) { latitude_ = value; }
    inline LatLong& mutable_latitude() { return latitude_; }
    inline const LatLong& get_latitude() const { return latitude_; }
    inline const LatLong& latitude() const { return latitude_; }

    static constexpr char const* LONGITUDE_NAME = "longitude";
    inline void clear_longitude() { longitude_.clear(); }
    inline void set_longitude(const LatLong& value) { longitude_ = value; }
    inline void set_longitude(const LatLong&& value) { longitude_ = value; }
    inline LatLong& mutable_longitude() { return longitude_; }
    inline const LatLong& get_longitude() const { return longitude_; }
    inline const LatLong& longitude() const { return longitude_; }

    static constexpr char const* ANTENNA_ALT_NAME = "antenna_alt";
    inline void clear_antenna_alt() { antenna_alt_.clear(); }
    inline void set_antenna_alt(const AltitudeType& value) { antenna_alt_ = value; }
    inline void set_antenna_alt(const AltitudeType&& value) { antenna_alt_ = value; }
    inline AltitudeType& mutable_antenna_alt() { return antenna_alt_; }
    inline const AltitudeType& get_antenna_alt() const { return antenna_alt_; }
    inline const AltitudeType& antenna_alt() const { return antenna_alt_; }

    static constexpr char const* GEOIDALTITUDE_NAME = "geoidAltitude";
    inline void clear_geoidAltitude() { geoidAltitude_.clear(); }
    inline void set_geoidAltitude(const AltitudeType& value) { geoidAltitude_ = value; }
    inline void set_geoidAltitude(const AltitudeType&& value) { geoidAltitude_ = value; }
    inline AltitudeType& mutable_geoidAltitude() { return geoidAltitude_; }
    inline const AltitudeType& get_geoidAltitude() const { return geoidAltitude_; }
    inline const AltitudeType& geoidAltitude() const { return geoidAltitude_; }

    static constexpr char const* TOTAL_ALT_NAME = "total_alt";
    inline void clear_total_alt() { total_alt_.clear(); }
    inline void set_total_alt(const AltitudeType& value) { total_alt_ = value; }
    inline void set_total_alt(const AltitudeType&& value) { total_alt_ = value; }
    inline AltitudeType& mutable_total_alt() { return total_alt_; }
    inline const AltitudeType& get_total_alt() const { return total_alt_; }
    inline const AltitudeType& total_alt() const { return total_alt_; }

    static constexpr char const* TIME_NAME = "time";
    inline void clear_time() { time_.clear(); }
    inline void set_time(const uint32_t& value) { time_ = value; }
    inline void set_time(const uint32_t&& value) { time_ = value; }
    inline uint32_t& mutable_time() { return time_.get(); }
    inline const uint32_t& get_time() const { return time_.get(); }
    inline uint32_t time() const { return time_.get(); }


    ::EmbeddedProto::Error serialize(::EmbeddedProto::WriteBufferInterface& buffer) const override
    {
      ::EmbeddedProto::Error return_value = ::EmbeddedProto::Error::NO_ERRORS;

      if(::EmbeddedProto::Error::NO_ERRORS == return_value)
      {
        return_value = latitude_.serialize_with_id(static_cast<uint32_t>(FieldNumber::LATITUDE), buffer, false);
      }

      if(::EmbeddedProto::Error::NO_ERRORS == return_value)
      {
        return_value = longitude_.serialize_with_id(static_cast<uint32_t>(FieldNumber::LONGITUDE), buffer, false);
      }

      if(::EmbeddedProto::Error::NO_ERRORS == return_value)
      {
        return_value = antenna_alt_.serialize_with_id(static_cast<uint32_t>(FieldNumber::ANTENNA_ALT), buffer, false);
      }

      if(::EmbeddedProto::Error::NO_ERRORS == return_value)
      {
        return_value = geoidAltitude_.serialize_with_id(static_cast<uint32_t>(FieldNumber::GEOIDALTITUDE), buffer, false);
      }

      if(::EmbeddedProto::Error::NO_ERRORS == return_value)
      {
        return_value = total_alt_.serialize_with_id(static_cast<uint32_t>(FieldNumber::TOTAL_ALT), buffer, false);
      }

      if((0U != time_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = time_.serialize_with_id(static_cast<uint32_t>(FieldNumber::TIME), buffer, false);
      }

      return return_value;
    };

    ::EmbeddedProto::Error deserialize(::EmbeddedProto::ReadBufferInterface& buffer) override
    {
      ::EmbeddedProto::Error return_value = ::EmbeddedProto::Error::NO_ERRORS;
      ::EmbeddedProto::WireFormatter::WireType wire_type = ::EmbeddedProto::WireFormatter::WireType::VARINT;
      uint32_t id_number = 0;
      FieldNumber id_tag = FieldNumber::NOT_SET;

      ::EmbeddedProto::Error tag_value = ::EmbeddedProto::WireFormatter::DeserializeTag(buffer, wire_type, id_number);
      while((::EmbeddedProto::Error::NO_ERRORS == return_value) && (::EmbeddedProto::Error::NO_ERRORS == tag_value))
      {
        id_tag = static_cast<FieldNumber>(id_number);
        switch(id_tag)
        {
          case FieldNumber::LATITUDE:
            return_value = latitude_.deserialize_check_type(buffer, wire_type);
            break;

          case FieldNumber::LONGITUDE:
            return_value = longitude_.deserialize_check_type(buffer, wire_type);
            break;

          case FieldNumber::ANTENNA_ALT:
            return_value = antenna_alt_.deserialize_check_type(buffer, wire_type);
            break;

          case FieldNumber::GEOIDALTITUDE:
            return_value = geoidAltitude_.deserialize_check_type(buffer, wire_type);
            break;

          case FieldNumber::TOTAL_ALT:
            return_value = total_alt_.deserialize_check_type(buffer, wire_type);
            break;

          case FieldNumber::TIME:
            return_value = time_.deserialize_check_type(buffer, wire_type);
            break;

          case FieldNumber::NOT_SET:
            return_value = ::EmbeddedProto::Error::INVALID_FIELD_ID;
            break;

          default:
            return_value = skip_unknown_field(buffer, wire_type);
            break;
        }

        if(::EmbeddedProto::Error::NO_ERRORS == return_value)
        {
          // Read the next tag.
          tag_value = ::EmbeddedProto::WireFormatter::DeserializeTag(buffer, wire_type, id_number);
        }
      }

      // When an error was detect while reading the tag but no other errors where found, set it in the return value.
      if((::EmbeddedProto::Error::NO_ERRORS == return_value)
         && (::EmbeddedProto::Error::NO_ERRORS != tag_value)
         && (::EmbeddedProto::Error::END_OF_BUFFER != tag_value)) // The end of the buffer is not an array in this case.
      {
        return_value = tag_value;
      }

      return return_value;
    };

    void clear() override
    {
      clear_latitude();
      clear_longitude();
      clear_antenna_alt();
      clear_geoidAltitude();
      clear_total_alt();
      clear_time();

    }

    static char const* field_number_to_name(const FieldNumber fieldNumber)
    {
      char const* name = nullptr;
      switch(fieldNumber)
      {
        case FieldNumber::LATITUDE:
          name = LATITUDE_NAME;
          break;
        case FieldNumber::LONGITUDE:
          name = LONGITUDE_NAME;
          break;
        case FieldNumber::ANTENNA_ALT:
          name = ANTENNA_ALT_NAME;
          break;
        case FieldNumber::GEOIDALTITUDE:
          name = GEOIDALTITUDE_NAME;
          break;
        case FieldNumber::TOTAL_ALT:
          name = TOTAL_ALT_NAME;
          break;
        case FieldNumber::TIME:
          name = TIME_NAME;
          break;
        default:
          name = "Invalid FieldNumber";
          break;
      }
      return name;
    }

#ifdef MSG_TO_STRING

    ::EmbeddedProto::string_view to_string(::EmbeddedProto::string_view& str) const
    {
      return this->to_string(str, 0, nullptr, true);
    }

    ::EmbeddedProto::string_view to_string(::EmbeddedProto::string_view& str, const uint32_t indent_level, char const* name, const bool first_field) const override
    {
      ::EmbeddedProto::string_view left_chars = str;
      int32_t n_chars_used = 0;

      if(!first_field)
      {
        // Add a comma behind the previous field.
        n_chars_used = snprintf(left_chars.data, left_chars.size, ",\n");
        if(0 < n_chars_used)
        {
          // Update the character pointer and characters left in the array.
          left_chars.data += n_chars_used;
          left_chars.size -= n_chars_used;
        }
      }

      if(nullptr != name)
      {
        if( 0 == indent_level)
        {
          n_chars_used = snprintf(left_chars.data, left_chars.size, "\"%s\": {\n", name);
        }
        else
        {
          n_chars_used = snprintf(left_chars.data, left_chars.size, "%*s\"%s\": {\n", indent_level, " ", name);
        }
      }
      else
      {
        if( 0 == indent_level)
        {
          n_chars_used = snprintf(left_chars.data, left_chars.size, "{\n");
        }
        else
        {
          n_chars_used = snprintf(left_chars.data, left_chars.size, "%*s{\n", indent_level, " ");
        }
      }
      
      if(0 < n_chars_used)
      {
        left_chars.data += n_chars_used;
        left_chars.size -= n_chars_used;
      }

      left_chars = latitude_.to_string(left_chars, indent_level + 2, LATITUDE_NAME, true);
      left_chars = longitude_.to_string(left_chars, indent_level + 2, LONGITUDE_NAME, false);
      left_chars = antenna_alt_.to_string(left_chars, indent_level + 2, ANTENNA_ALT_NAME, false);
      left_chars = geoidAltitude_.to_string(left_chars, indent_level + 2, GEOIDALTITUDE_NAME, false);
      left_chars = total_alt_.to_string(left_chars, indent_level + 2, TOTAL_ALT_NAME, false);
      left_chars = time_.to_string(left_chars, indent_level + 2, TIME_NAME, false);
  
      if( 0 == indent_level) 
      {
        n_chars_used = snprintf(left_chars.data, left_chars.size, "\n}");
      }
      else 
      {
        n_chars_used = snprintf(left_chars.data, left_chars.size, "\n%*s}", indent_level, " ");
      }

      if(0 < n_chars_used)
      {
        left_chars.data += n_chars_used;
        left_chars.size -= n_chars_used;
      }

      return left_chars;
    }

#endif // End of MSG_TO_STRING

  private:


      LatLong latitude_;
      LatLong longitude_;
      AltitudeType antenna_alt_;
      AltitudeType geoidAltitude_;
      AltitudeType total_alt_;
      EmbeddedProto::uint32 time_ = 0U;

};

class TelemetryMessage final: public ::EmbeddedProto::MessageInterface
{
  public:
    TelemetryMessage() = default;
    TelemetryMessage(const TelemetryMessage& rhs )
    {
      set_source(rhs.get_source());
      set_target(rhs.get_target());
      set_message_id(rhs.get_message_id());
      if(rhs.get_which_message() != which_message_)
      {
        // First delete the old object in the oneof.
        clear_message();
      }

      switch(rhs.get_which_message())
      {
        case FieldNumber::COORD:
          set_coord(rhs.get_coord());
          break;

        case FieldNumber::BARO:
          set_baro(rhs.get_baro());
          break;

        case FieldNumber::IMU:
          set_imu(rhs.get_imu());
          break;

        case FieldNumber::BAT:
          set_bat(rhs.get_bat());
          break;

        case FieldNumber::FLASHINFO:
          set_flashInfo(rhs.get_flashInfo());
          break;

        case FieldNumber::PRESSDMB:
          set_pressdmb(rhs.get_pressdmb());
          break;

        case FieldNumber::PRESSPBB:
          set_presspbb(rhs.get_presspbb());
          break;

        case FieldNumber::TEMPPBB:
          set_temppbb(rhs.get_temppbb());
          break;

        case FieldNumber::GPIO:
          set_gpio(rhs.get_gpio());
          break;

        case FieldNumber::PRESSRCU:
          set_pressrcu(rhs.get_pressrcu());
          break;

        case FieldNumber::TEMPRCU:
          set_temprcu(rhs.get_temprcu());
          break;

        case FieldNumber::NOS:
          set_nos(rhs.get_nos());
          break;

        case FieldNumber::RELAY:
          set_relay(rhs.get_relay());
          break;

        case FieldNumber::PADBOX:
          set_padbox(rhs.get_padbox());
          break;

        case FieldNumber::LR:
          set_lr(rhs.get_lr());
          break;

        case FieldNumber::TEMPSOB:
          set_tempsob(rhs.get_tempsob());
          break;

        case FieldNumber::IRTEMP:
          set_irtemp(rhs.get_irtemp());
          break;

        case FieldNumber::MEVSTATE:
          set_mevstate(rhs.get_mevstate());
          break;

        default:
          break;
      }

    }

    TelemetryMessage(const TelemetryMessage&& rhs ) noexcept
    {
      set_source(rhs.get_source());
      set_target(rhs.get_target());
      set_message_id(rhs.get_message_id());
      if(rhs.get_which_message() != which_message_)
      {
        // First delete the old object in the oneof.
        clear_message();
      }

      switch(rhs.get_which_message())
      {
        case FieldNumber::COORD:
          set_coord(rhs.get_coord());
          break;

        case FieldNumber::BARO:
          set_baro(rhs.get_baro());
          break;

        case FieldNumber::IMU:
          set_imu(rhs.get_imu());
          break;

        case FieldNumber::BAT:
          set_bat(rhs.get_bat());
          break;

        case FieldNumber::FLASHINFO:
          set_flashInfo(rhs.get_flashInfo());
          break;

        case FieldNumber::PRESSDMB:
          set_pressdmb(rhs.get_pressdmb());
          break;

        case FieldNumber::PRESSPBB:
          set_presspbb(rhs.get_presspbb());
          break;

        case FieldNumber::TEMPPBB:
          set_temppbb(rhs.get_temppbb());
          break;

        case FieldNumber::GPIO:
          set_gpio(rhs.get_gpio());
          break;

        case FieldNumber::PRESSRCU:
          set_pressrcu(rhs.get_pressrcu());
          break;

        case FieldNumber::TEMPRCU:
          set_temprcu(rhs.get_temprcu());
          break;

        case FieldNumber::NOS:
          set_nos(rhs.get_nos());
          break;

        case FieldNumber::RELAY:
          set_relay(rhs.get_relay());
          break;

        case FieldNumber::PADBOX:
          set_padbox(rhs.get_padbox());
          break;

        case FieldNumber::LR:
          set_lr(rhs.get_lr());
          break;

        case FieldNumber::TEMPSOB:
          set_tempsob(rhs.get_tempsob());
          break;

        case FieldNumber::IRTEMP:
          set_irtemp(rhs.get_irtemp());
          break;

        case FieldNumber::MEVSTATE:
          set_mevstate(rhs.get_mevstate());
          break;

        default:
          break;
      }

    }

    ~TelemetryMessage() override = default;

    enum class FieldNumber : uint32_t
    {
      NOT_SET = 0,
      SOURCE = 1,
      TARGET = 2,
      MESSAGE_ID = 3,
      COORD = 4,
      BARO = 5,
      IMU = 6,
      BAT = 7,
      FLASHINFO = 8,
      PRESSDMB = 9,
      PRESSPBB = 10,
      TEMPPBB = 11,
      GPIO = 12,
      PRESSRCU = 13,
      TEMPRCU = 14,
      NOS = 15,
      RELAY = 16,
      PADBOX = 17,
      LR = 18,
      TEMPSOB = 19,
      IRTEMP = 20,
      MEVSTATE = 21
    };

    TelemetryMessage& operator=(const TelemetryMessage& rhs)
    {
      set_source(rhs.get_source());
      set_target(rhs.get_target());
      set_message_id(rhs.get_message_id());
      if(rhs.get_which_message() != which_message_)
      {
        // First delete the old object in the oneof.
        clear_message();
      }

      switch(rhs.get_which_message())
      {
        case FieldNumber::COORD:
          set_coord(rhs.get_coord());
          break;

        case FieldNumber::BARO:
          set_baro(rhs.get_baro());
          break;

        case FieldNumber::IMU:
          set_imu(rhs.get_imu());
          break;

        case FieldNumber::BAT:
          set_bat(rhs.get_bat());
          break;

        case FieldNumber::FLASHINFO:
          set_flashInfo(rhs.get_flashInfo());
          break;

        case FieldNumber::PRESSDMB:
          set_pressdmb(rhs.get_pressdmb());
          break;

        case FieldNumber::PRESSPBB:
          set_presspbb(rhs.get_presspbb());
          break;

        case FieldNumber::TEMPPBB:
          set_temppbb(rhs.get_temppbb());
          break;

        case FieldNumber::GPIO:
          set_gpio(rhs.get_gpio());
          break;

        case FieldNumber::PRESSRCU:
          set_pressrcu(rhs.get_pressrcu());
          break;

        case FieldNumber::TEMPRCU:
          set_temprcu(rhs.get_temprcu());
          break;

        case FieldNumber::NOS:
          set_nos(rhs.get_nos());
          break;

        case FieldNumber::RELAY:
          set_relay(rhs.get_relay());
          break;

        case FieldNumber::PADBOX:
          set_padbox(rhs.get_padbox());
          break;

        case FieldNumber::LR:
          set_lr(rhs.get_lr());
          break;

        case FieldNumber::TEMPSOB:
          set_tempsob(rhs.get_tempsob());
          break;

        case FieldNumber::IRTEMP:
          set_irtemp(rhs.get_irtemp());
          break;

        case FieldNumber::MEVSTATE:
          set_mevstate(rhs.get_mevstate());
          break;

        default:
          break;
      }

      return *this;
    }

    TelemetryMessage& operator=(const TelemetryMessage&& rhs) noexcept
    {
      set_source(rhs.get_source());
      set_target(rhs.get_target());
      set_message_id(rhs.get_message_id());
      if(rhs.get_which_message() != which_message_)
      {
        // First delete the old object in the oneof.
        clear_message();
      }

      switch(rhs.get_which_message())
      {
        case FieldNumber::COORD:
          set_coord(rhs.get_coord());
          break;

        case FieldNumber::BARO:
          set_baro(rhs.get_baro());
          break;

        case FieldNumber::IMU:
          set_imu(rhs.get_imu());
          break;

        case FieldNumber::BAT:
          set_bat(rhs.get_bat());
          break;

        case FieldNumber::FLASHINFO:
          set_flashInfo(rhs.get_flashInfo());
          break;

        case FieldNumber::PRESSDMB:
          set_pressdmb(rhs.get_pressdmb());
          break;

        case FieldNumber::PRESSPBB:
          set_presspbb(rhs.get_presspbb());
          break;

        case FieldNumber::TEMPPBB:
          set_temppbb(rhs.get_temppbb());
          break;

        case FieldNumber::GPIO:
          set_gpio(rhs.get_gpio());
          break;

        case FieldNumber::PRESSRCU:
          set_pressrcu(rhs.get_pressrcu());
          break;

        case FieldNumber::TEMPRCU:
          set_temprcu(rhs.get_temprcu());
          break;

        case FieldNumber::NOS:
          set_nos(rhs.get_nos());
          break;

        case FieldNumber::RELAY:
          set_relay(rhs.get_relay());
          break;

        case FieldNumber::PADBOX:
          set_padbox(rhs.get_padbox());
          break;

        case FieldNumber::LR:
          set_lr(rhs.get_lr());
          break;

        case FieldNumber::TEMPSOB:
          set_tempsob(rhs.get_tempsob());
          break;

        case FieldNumber::IRTEMP:
          set_irtemp(rhs.get_irtemp());
          break;

        case FieldNumber::MEVSTATE:
          set_mevstate(rhs.get_mevstate());
          break;

        default:
          break;
      }

      return *this;
    }

    static constexpr char const* SOURCE_NAME = "source";
    inline void clear_source() { source_.clear(); }
    inline void set_source(const Node& value) { source_ = value; }
    inline void set_source(const Node&& value) { source_ = value; }
    inline const Node& get_source() const { return source_.get(); }
    inline Node source() const { return source_.get(); }

    static constexpr char const* TARGET_NAME = "target";
    inline void clear_target() { target_.clear(); }
    inline void set_target(const Node& value) { target_ = value; }
    inline void set_target(const Node&& value) { target_ = value; }
    inline const Node& get_target() const { return target_.get(); }
    inline Node target() const { return target_.get(); }

    static constexpr char const* MESSAGE_ID_NAME = "message_id";
    inline void clear_message_id() { message_id_.clear(); }
    inline void set_message_id(const uint32_t& value) { message_id_ = value; }
    inline void set_message_id(const uint32_t&& value) { message_id_ = value; }
    inline uint32_t& mutable_message_id() { return message_id_.get(); }
    inline const uint32_t& get_message_id() const { return message_id_.get(); }
    inline uint32_t message_id() const { return message_id_.get(); }

    FieldNumber get_which_message() const { return which_message_; }

    static constexpr char const* COORD_NAME = "coord";
    inline bool has_coord() const
    {
      return FieldNumber::COORD == which_message_;
    }
    inline void clear_coord()
    {
      if(FieldNumber::COORD == which_message_)
      {
        which_message_ = FieldNumber::NOT_SET;
        message_.coord_.~GPS();
      }
    }
    inline void set_coord(const GPS& value)
    {
      if(FieldNumber::COORD != which_message_)
      {
        init_message(FieldNumber::COORD);
      }
      message_.coord_ = value;
    }
    inline void set_coord(const GPS&& value)
    {
      if(FieldNumber::COORD != which_message_)
      {
        init_message(FieldNumber::COORD);
      }
      message_.coord_ = value;
    }
    inline GPS& mutable_coord()
    {
      if(FieldNumber::COORD != which_message_)
      {
        init_message(FieldNumber::COORD);
      }
      return message_.coord_;
    }
    inline const GPS& get_coord() const { return message_.coord_; }
    inline const GPS& coord() const { return message_.coord_; }

    static constexpr char const* BARO_NAME = "baro";
    inline bool has_baro() const
    {
      return FieldNumber::BARO == which_message_;
    }
    inline void clear_baro()
    {
      if(FieldNumber::BARO == which_message_)
      {
        which_message_ = FieldNumber::NOT_SET;
        message_.baro_.~Baro();
      }
    }
    inline void set_baro(const Baro& value)
    {
      if(FieldNumber::BARO != which_message_)
      {
        init_message(FieldNumber::BARO);
      }
      message_.baro_ = value;
    }
    inline void set_baro(const Baro&& value)
    {
      if(FieldNumber::BARO != which_message_)
      {
        init_message(FieldNumber::BARO);
      }
      message_.baro_ = value;
    }
    inline Baro& mutable_baro()
    {
      if(FieldNumber::BARO != which_message_)
      {
        init_message(FieldNumber::BARO);
      }
      return message_.baro_;
    }
    inline const Baro& get_baro() const { return message_.baro_; }
    inline const Baro& baro() const { return message_.baro_; }

    static constexpr char const* IMU_NAME = "imu";
    inline bool has_imu() const
    {
      return FieldNumber::IMU == which_message_;
    }
    inline void clear_imu()
    {
      if(FieldNumber::IMU == which_message_)
      {
        which_message_ = FieldNumber::NOT_SET;
        message_.imu_.~IMU();
      }
    }
    inline void set_imu(const IMU& value)
    {
      if(FieldNumber::IMU != which_message_)
      {
        init_message(FieldNumber::IMU);
      }
      message_.imu_ = value;
    }
    inline void set_imu(const IMU&& value)
    {
      if(FieldNumber::IMU != which_message_)
      {
        init_message(FieldNumber::IMU);
      }
      message_.imu_ = value;
    }
    inline IMU& mutable_imu()
    {
      if(FieldNumber::IMU != which_message_)
      {
        init_message(FieldNumber::IMU);
      }
      return message_.imu_;
    }
    inline const IMU& get_imu() const { return message_.imu_; }
    inline const IMU& imu() const { return message_.imu_; }

    static constexpr char const* BAT_NAME = "bat";
    inline bool has_bat() const
    {
      return FieldNumber::BAT == which_message_;
    }
    inline void clear_bat()
    {
      if(FieldNumber::BAT == which_message_)
      {
        which_message_ = FieldNumber::NOT_SET;
        message_.bat_.~Battery();
      }
    }
    inline void set_bat(const Battery& value)
    {
      if(FieldNumber::BAT != which_message_)
      {
        init_message(FieldNumber::BAT);
      }
      message_.bat_ = value;
    }
    inline void set_bat(const Battery&& value)
    {
      if(FieldNumber::BAT != which_message_)
      {
        init_message(FieldNumber::BAT);
      }
      message_.bat_ = value;
    }
    inline Battery& mutable_bat()
    {
      if(FieldNumber::BAT != which_message_)
      {
        init_message(FieldNumber::BAT);
      }
      return message_.bat_;
    }
    inline const Battery& get_bat() const { return message_.bat_; }
    inline const Battery& bat() const { return message_.bat_; }

    static constexpr char const* FLASHINFO_NAME = "flashInfo";
    inline bool has_flashInfo() const
    {
      return FieldNumber::FLASHINFO == which_message_;
    }
    inline void clear_flashInfo()
    {
      if(FieldNumber::FLASHINFO == which_message_)
      {
        which_message_ = FieldNumber::NOT_SET;
        message_.flashInfo_.~Flash();
      }
    }
    inline void set_flashInfo(const Flash& value)
    {
      if(FieldNumber::FLASHINFO != which_message_)
      {
        init_message(FieldNumber::FLASHINFO);
      }
      message_.flashInfo_ = value;
    }
    inline void set_flashInfo(const Flash&& value)
    {
      if(FieldNumber::FLASHINFO != which_message_)
      {
        init_message(FieldNumber::FLASHINFO);
      }
      message_.flashInfo_ = value;
    }
    inline Flash& mutable_flashInfo()
    {
      if(FieldNumber::FLASHINFO != which_message_)
      {
        init_message(FieldNumber::FLASHINFO);
      }
      return message_.flashInfo_;
    }
    inline const Flash& get_flashInfo() const { return message_.flashInfo_; }
    inline const Flash& flashInfo() const { return message_.flashInfo_; }

    static constexpr char const* PRESSDMB_NAME = "pressdmb";
    inline bool has_pressdmb() const
    {
      return FieldNumber::PRESSDMB == which_message_;
    }
    inline void clear_pressdmb()
    {
      if(FieldNumber::PRESSDMB == which_message_)
      {
        which_message_ = FieldNumber::NOT_SET;
        message_.pressdmb_.~DMBPressure();
      }
    }
    inline void set_pressdmb(const DMBPressure& value)
    {
      if(FieldNumber::PRESSDMB != which_message_)
      {
        init_message(FieldNumber::PRESSDMB);
      }
      message_.pressdmb_ = value;
    }
    inline void set_pressdmb(const DMBPressure&& value)
    {
      if(FieldNumber::PRESSDMB != which_message_)
      {
        init_message(FieldNumber::PRESSDMB);
      }
      message_.pressdmb_ = value;
    }
    inline DMBPressure& mutable_pressdmb()
    {
      if(FieldNumber::PRESSDMB != which_message_)
      {
        init_message(FieldNumber::PRESSDMB);
      }
      return message_.pressdmb_;
    }
    inline const DMBPressure& get_pressdmb() const { return message_.pressdmb_; }
    inline const DMBPressure& pressdmb() const { return message_.pressdmb_; }

    static constexpr char const* PRESSPBB_NAME = "presspbb";
    inline bool has_presspbb() const
    {
      return FieldNumber::PRESSPBB == which_message_;
    }
    inline void clear_presspbb()
    {
      if(FieldNumber::PRESSPBB == which_message_)
      {
        which_message_ = FieldNumber::NOT_SET;
        message_.presspbb_.~PBBPressure();
      }
    }
    inline void set_presspbb(const PBBPressure& value)
    {
      if(FieldNumber::PRESSPBB != which_message_)
      {
        init_message(FieldNumber::PRESSPBB);
      }
      message_.presspbb_ = value;
    }
    inline void set_presspbb(const PBBPressure&& value)
    {
      if(FieldNumber::PRESSPBB != which_message_)
      {
        init_message(FieldNumber::PRESSPBB);
      }
      message_.presspbb_ = value;
    }
    inline PBBPressure& mutable_presspbb()
    {
      if(FieldNumber::PRESSPBB != which_message_)
      {
        init_message(FieldNumber::PRESSPBB);
      }
      return message_.presspbb_;
    }
    inline const PBBPressure& get_presspbb() const { return message_.presspbb_; }
    inline const PBBPressure& presspbb() const { return message_.presspbb_; }

    static constexpr char const* TEMPPBB_NAME = "temppbb";
    inline bool has_temppbb() const
    {
      return FieldNumber::TEMPPBB == which_message_;
    }
    inline void clear_temppbb()
    {
      if(FieldNumber::TEMPPBB == which_message_)
      {
        which_message_ = FieldNumber::NOT_SET;
        message_.temppbb_.~PBBTemp();
      }
    }
    inline void set_temppbb(const PBBTemp& value)
    {
      if(FieldNumber::TEMPPBB != which_message_)
      {
        init_message(FieldNumber::TEMPPBB);
      }
      message_.temppbb_ = value;
    }
    inline void set_temppbb(const PBBTemp&& value)
    {
      if(FieldNumber::TEMPPBB != which_message_)
      {
        init_message(FieldNumber::TEMPPBB);
      }
      message_.temppbb_ = value;
    }
    inline PBBTemp& mutable_temppbb()
    {
      if(FieldNumber::TEMPPBB != which_message_)
      {
        init_message(FieldNumber::TEMPPBB);
      }
      return message_.temppbb_;
    }
    inline const PBBTemp& get_temppbb() const { return message_.temppbb_; }
    inline const PBBTemp& temppbb() const { return message_.temppbb_; }

    static constexpr char const* GPIO_NAME = "gpio";
    inline bool has_gpio() const
    {
      return FieldNumber::GPIO == which_message_;
    }
    inline void clear_gpio()
    {
      if(FieldNumber::GPIO == which_message_)
      {
        which_message_ = FieldNumber::NOT_SET;
        message_.gpio_.~CombustionControlStatus();
      }
    }
    inline void set_gpio(const CombustionControlStatus& value)
    {
      if(FieldNumber::GPIO != which_message_)
      {
        init_message(FieldNumber::GPIO);
      }
      message_.gpio_ = value;
    }
    inline void set_gpio(const CombustionControlStatus&& value)
    {
      if(FieldNumber::GPIO != which_message_)
      {
        init_message(FieldNumber::GPIO);
      }
      message_.gpio_ = value;
    }
    inline CombustionControlStatus& mutable_gpio()
    {
      if(FieldNumber::GPIO != which_message_)
      {
        init_message(FieldNumber::GPIO);
      }
      return message_.gpio_;
    }
    inline const CombustionControlStatus& get_gpio() const { return message_.gpio_; }
    inline const CombustionControlStatus& gpio() const { return message_.gpio_; }

    static constexpr char const* PRESSRCU_NAME = "pressrcu";
    inline bool has_pressrcu() const
    {
      return FieldNumber::PRESSRCU == which_message_;
    }
    inline void clear_pressrcu()
    {
      if(FieldNumber::PRESSRCU == which_message_)
      {
        which_message_ = FieldNumber::NOT_SET;
        message_.pressrcu_.~RCUPressure();
      }
    }
    inline void set_pressrcu(const RCUPressure& value)
    {
      if(FieldNumber::PRESSRCU != which_message_)
      {
        init_message(FieldNumber::PRESSRCU);
      }
      message_.pressrcu_ = value;
    }
    inline void set_pressrcu(const RCUPressure&& value)
    {
      if(FieldNumber::PRESSRCU != which_message_)
      {
        init_message(FieldNumber::PRESSRCU);
      }
      message_.pressrcu_ = value;
    }
    inline RCUPressure& mutable_pressrcu()
    {
      if(FieldNumber::PRESSRCU != which_message_)
      {
        init_message(FieldNumber::PRESSRCU);
      }
      return message_.pressrcu_;
    }
    inline const RCUPressure& get_pressrcu() const { return message_.pressrcu_; }
    inline const RCUPressure& pressrcu() const { return message_.pressrcu_; }

    static constexpr char const* TEMPRCU_NAME = "temprcu";
    inline bool has_temprcu() const
    {
      return FieldNumber::TEMPRCU == which_message_;
    }
    inline void clear_temprcu()
    {
      if(FieldNumber::TEMPRCU == which_message_)
      {
        which_message_ = FieldNumber::NOT_SET;
        message_.temprcu_.~RCUTemp();
      }
    }
    inline void set_temprcu(const RCUTemp& value)
    {
      if(FieldNumber::TEMPRCU != which_message_)
      {
        init_message(FieldNumber::TEMPRCU);
      }
      message_.temprcu_ = value;
    }
    inline void set_temprcu(const RCUTemp&& value)
    {
      if(FieldNumber::TEMPRCU != which_message_)
      {
        init_message(FieldNumber::TEMPRCU);
      }
      message_.temprcu_ = value;
    }
    inline RCUTemp& mutable_temprcu()
    {
      if(FieldNumber::TEMPRCU != which_message_)
      {
        init_message(FieldNumber::TEMPRCU);
      }
      return message_.temprcu_;
    }
    inline const RCUTemp& get_temprcu() const { return message_.temprcu_; }
    inline const RCUTemp& temprcu() const { return message_.temprcu_; }

    static constexpr char const* NOS_NAME = "nos";
    inline bool has_nos() const
    {
      return FieldNumber::NOS == which_message_;
    }
    inline void clear_nos()
    {
      if(FieldNumber::NOS == which_message_)
      {
        which_message_ = FieldNumber::NOT_SET;
        message_.nos_.~NOSLoadCell();
      }
    }
    inline void set_nos(const NOSLoadCell& value)
    {
      if(FieldNumber::NOS != which_message_)
      {
        init_message(FieldNumber::NOS);
      }
      message_.nos_ = value;
    }
    inline void set_nos(const NOSLoadCell&& value)
    {
      if(FieldNumber::NOS != which_message_)
      {
        init_message(FieldNumber::NOS);
      }
      message_.nos_ = value;
    }
    inline NOSLoadCell& mutable_nos()
    {
      if(FieldNumber::NOS != which_message_)
      {
        init_message(FieldNumber::NOS);
      }
      return message_.nos_;
    }
    inline const NOSLoadCell& get_nos() const { return message_.nos_; }
    inline const NOSLoadCell& nos() const { return message_.nos_; }

    static constexpr char const* RELAY_NAME = "relay";
    inline bool has_relay() const
    {
      return FieldNumber::RELAY == which_message_;
    }
    inline void clear_relay()
    {
      if(FieldNumber::RELAY == which_message_)
      {
        which_message_ = FieldNumber::NOT_SET;
        message_.relay_.~RelayStatus();
      }
    }
    inline void set_relay(const RelayStatus& value)
    {
      if(FieldNumber::RELAY != which_message_)
      {
        init_message(FieldNumber::RELAY);
      }
      message_.relay_ = value;
    }
    inline void set_relay(const RelayStatus&& value)
    {
      if(FieldNumber::RELAY != which_message_)
      {
        init_message(FieldNumber::RELAY);
      }
      message_.relay_ = value;
    }
    inline RelayStatus& mutable_relay()
    {
      if(FieldNumber::RELAY != which_message_)
      {
        init_message(FieldNumber::RELAY);
      }
      return message_.relay_;
    }
    inline const RelayStatus& get_relay() const { return message_.relay_; }
    inline const RelayStatus& relay() const { return message_.relay_; }

    static constexpr char const* PADBOX_NAME = "padbox";
    inline bool has_padbox() const
    {
      return FieldNumber::PADBOX == which_message_;
    }
    inline void clear_padbox()
    {
      if(FieldNumber::PADBOX == which_message_)
      {
        which_message_ = FieldNumber::NOT_SET;
        message_.padbox_.~PadBoxStatus();
      }
    }
    inline void set_padbox(const PadBoxStatus& value)
    {
      if(FieldNumber::PADBOX != which_message_)
      {
        init_message(FieldNumber::PADBOX);
      }
      message_.padbox_ = value;
    }
    inline void set_padbox(const PadBoxStatus&& value)
    {
      if(FieldNumber::PADBOX != which_message_)
      {
        init_message(FieldNumber::PADBOX);
      }
      message_.padbox_ = value;
    }
    inline PadBoxStatus& mutable_padbox()
    {
      if(FieldNumber::PADBOX != which_message_)
      {
        init_message(FieldNumber::PADBOX);
      }
      return message_.padbox_;
    }
    inline const PadBoxStatus& get_padbox() const { return message_.padbox_; }
    inline const PadBoxStatus& padbox() const { return message_.padbox_; }

    static constexpr char const* LR_NAME = "lr";
    inline bool has_lr() const
    {
      return FieldNumber::LR == which_message_;
    }
    inline void clear_lr()
    {
      if(FieldNumber::LR == which_message_)
      {
        which_message_ = FieldNumber::NOT_SET;
        message_.lr_.~LRLoadCell();
      }
    }
    inline void set_lr(const LRLoadCell& value)
    {
      if(FieldNumber::LR != which_message_)
      {
        init_message(FieldNumber::LR);
      }
      message_.lr_ = value;
    }
    inline void set_lr(const LRLoadCell&& value)
    {
      if(FieldNumber::LR != which_message_)
      {
        init_message(FieldNumber::LR);
      }
      message_.lr_ = value;
    }
    inline LRLoadCell& mutable_lr()
    {
      if(FieldNumber::LR != which_message_)
      {
        init_message(FieldNumber::LR);
      }
      return message_.lr_;
    }
    inline const LRLoadCell& get_lr() const { return message_.lr_; }
    inline const LRLoadCell& lr() const { return message_.lr_; }

    static constexpr char const* TEMPSOB_NAME = "tempsob";
    inline bool has_tempsob() const
    {
      return FieldNumber::TEMPSOB == which_message_;
    }
    inline void clear_tempsob()
    {
      if(FieldNumber::TEMPSOB == which_message_)
      {
        which_message_ = FieldNumber::NOT_SET;
        message_.tempsob_.~SOBTemp();
      }
    }
    inline void set_tempsob(const SOBTemp& value)
    {
      if(FieldNumber::TEMPSOB != which_message_)
      {
        init_message(FieldNumber::TEMPSOB);
      }
      message_.tempsob_ = value;
    }
    inline void set_tempsob(const SOBTemp&& value)
    {
      if(FieldNumber::TEMPSOB != which_message_)
      {
        init_message(FieldNumber::TEMPSOB);
      }
      message_.tempsob_ = value;
    }
    inline SOBTemp& mutable_tempsob()
    {
      if(FieldNumber::TEMPSOB != which_message_)
      {
        init_message(FieldNumber::TEMPSOB);
      }
      return message_.tempsob_;
    }
    inline const SOBTemp& get_tempsob() const { return message_.tempsob_; }
    inline const SOBTemp& tempsob() const { return message_.tempsob_; }

    static constexpr char const* IRTEMP_NAME = "irtemp";
    inline bool has_irtemp() const
    {
      return FieldNumber::IRTEMP == which_message_;
    }
    inline void clear_irtemp()
    {
      if(FieldNumber::IRTEMP == which_message_)
      {
        which_message_ = FieldNumber::NOT_SET;
        message_.irtemp_.~IRTemperature();
      }
    }
    inline void set_irtemp(const IRTemperature& value)
    {
      if(FieldNumber::IRTEMP != which_message_)
      {
        init_message(FieldNumber::IRTEMP);
      }
      message_.irtemp_ = value;
    }
    inline void set_irtemp(const IRTemperature&& value)
    {
      if(FieldNumber::IRTEMP != which_message_)
      {
        init_message(FieldNumber::IRTEMP);
      }
      message_.irtemp_ = value;
    }
    inline IRTemperature& mutable_irtemp()
    {
      if(FieldNumber::IRTEMP != which_message_)
      {
        init_message(FieldNumber::IRTEMP);
      }
      return message_.irtemp_;
    }
    inline const IRTemperature& get_irtemp() const { return message_.irtemp_; }
    inline const IRTemperature& irtemp() const { return message_.irtemp_; }

    static constexpr char const* MEVSTATE_NAME = "mevstate";
    inline bool has_mevstate() const
    {
      return FieldNumber::MEVSTATE == which_message_;
    }
    inline void clear_mevstate()
    {
      if(FieldNumber::MEVSTATE == which_message_)
      {
        which_message_ = FieldNumber::NOT_SET;
        message_.mevstate_.~MEVState();
      }
    }
    inline void set_mevstate(const MEVState& value)
    {
      if(FieldNumber::MEVSTATE != which_message_)
      {
        init_message(FieldNumber::MEVSTATE);
      }
      message_.mevstate_ = value;
    }
    inline void set_mevstate(const MEVState&& value)
    {
      if(FieldNumber::MEVSTATE != which_message_)
      {
        init_message(FieldNumber::MEVSTATE);
      }
      message_.mevstate_ = value;
    }
    inline MEVState& mutable_mevstate()
    {
      if(FieldNumber::MEVSTATE != which_message_)
      {
        init_message(FieldNumber::MEVSTATE);
      }
      return message_.mevstate_;
    }
    inline const MEVState& get_mevstate() const { return message_.mevstate_; }
    inline const MEVState& mevstate() const { return message_.mevstate_; }


    ::EmbeddedProto::Error serialize(::EmbeddedProto::WriteBufferInterface& buffer) const override
    {
      ::EmbeddedProto::Error return_value = ::EmbeddedProto::Error::NO_ERRORS;

      if((static_cast<Node>(0) != source_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = source_.serialize_with_id(static_cast<uint32_t>(FieldNumber::SOURCE), buffer, false);
      }

      if((static_cast<Node>(0) != target_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = target_.serialize_with_id(static_cast<uint32_t>(FieldNumber::TARGET), buffer, false);
      }

      if((0U != message_id_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = message_id_.serialize_with_id(static_cast<uint32_t>(FieldNumber::MESSAGE_ID), buffer, false);
      }

      switch(which_message_)
      {
        case FieldNumber::COORD:
          if(has_coord() && (::EmbeddedProto::Error::NO_ERRORS == return_value))
          {
            return_value = message_.coord_.serialize_with_id(static_cast<uint32_t>(FieldNumber::COORD), buffer, true);
          }
          break;

        case FieldNumber::BARO:
          if(has_baro() && (::EmbeddedProto::Error::NO_ERRORS == return_value))
          {
            return_value = message_.baro_.serialize_with_id(static_cast<uint32_t>(FieldNumber::BARO), buffer, true);
          }
          break;

        case FieldNumber::IMU:
          if(has_imu() && (::EmbeddedProto::Error::NO_ERRORS == return_value))
          {
            return_value = message_.imu_.serialize_with_id(static_cast<uint32_t>(FieldNumber::IMU), buffer, true);
          }
          break;

        case FieldNumber::BAT:
          if(has_bat() && (::EmbeddedProto::Error::NO_ERRORS == return_value))
          {
            return_value = message_.bat_.serialize_with_id(static_cast<uint32_t>(FieldNumber::BAT), buffer, true);
          }
          break;

        case FieldNumber::FLASHINFO:
          if(has_flashInfo() && (::EmbeddedProto::Error::NO_ERRORS == return_value))
          {
            return_value = message_.flashInfo_.serialize_with_id(static_cast<uint32_t>(FieldNumber::FLASHINFO), buffer, true);
          }
          break;

        case FieldNumber::PRESSDMB:
          if(has_pressdmb() && (::EmbeddedProto::Error::NO_ERRORS == return_value))
          {
            return_value = message_.pressdmb_.serialize_with_id(static_cast<uint32_t>(FieldNumber::PRESSDMB), buffer, true);
          }
          break;

        case FieldNumber::PRESSPBB:
          if(has_presspbb() && (::EmbeddedProto::Error::NO_ERRORS == return_value))
          {
            return_value = message_.presspbb_.serialize_with_id(static_cast<uint32_t>(FieldNumber::PRESSPBB), buffer, true);
          }
          break;

        case FieldNumber::TEMPPBB:
          if(has_temppbb() && (::EmbeddedProto::Error::NO_ERRORS == return_value))
          {
            return_value = message_.temppbb_.serialize_with_id(static_cast<uint32_t>(FieldNumber::TEMPPBB), buffer, true);
          }
          break;

        case FieldNumber::GPIO:
          if(has_gpio() && (::EmbeddedProto::Error::NO_ERRORS == return_value))
          {
            return_value = message_.gpio_.serialize_with_id(static_cast<uint32_t>(FieldNumber::GPIO), buffer, true);
          }
          break;

        case FieldNumber::PRESSRCU:
          if(has_pressrcu() && (::EmbeddedProto::Error::NO_ERRORS == return_value))
          {
            return_value = message_.pressrcu_.serialize_with_id(static_cast<uint32_t>(FieldNumber::PRESSRCU), buffer, true);
          }
          break;

        case FieldNumber::TEMPRCU:
          if(has_temprcu() && (::EmbeddedProto::Error::NO_ERRORS == return_value))
          {
            return_value = message_.temprcu_.serialize_with_id(static_cast<uint32_t>(FieldNumber::TEMPRCU), buffer, true);
          }
          break;

        case FieldNumber::NOS:
          if(has_nos() && (::EmbeddedProto::Error::NO_ERRORS == return_value))
          {
            return_value = message_.nos_.serialize_with_id(static_cast<uint32_t>(FieldNumber::NOS), buffer, true);
          }
          break;

        case FieldNumber::RELAY:
          if(has_relay() && (::EmbeddedProto::Error::NO_ERRORS == return_value))
          {
            return_value = message_.relay_.serialize_with_id(static_cast<uint32_t>(FieldNumber::RELAY), buffer, true);
          }
          break;

        case FieldNumber::PADBOX:
          if(has_padbox() && (::EmbeddedProto::Error::NO_ERRORS == return_value))
          {
            return_value = message_.padbox_.serialize_with_id(static_cast<uint32_t>(FieldNumber::PADBOX), buffer, true);
          }
          break;

        case FieldNumber::LR:
          if(has_lr() && (::EmbeddedProto::Error::NO_ERRORS == return_value))
          {
            return_value = message_.lr_.serialize_with_id(static_cast<uint32_t>(FieldNumber::LR), buffer, true);
          }
          break;

        case FieldNumber::TEMPSOB:
          if(has_tempsob() && (::EmbeddedProto::Error::NO_ERRORS == return_value))
          {
            return_value = message_.tempsob_.serialize_with_id(static_cast<uint32_t>(FieldNumber::TEMPSOB), buffer, true);
          }
          break;

        case FieldNumber::IRTEMP:
          if(has_irtemp() && (::EmbeddedProto::Error::NO_ERRORS == return_value))
          {
            return_value = message_.irtemp_.serialize_with_id(static_cast<uint32_t>(FieldNumber::IRTEMP), buffer, true);
          }
          break;

        case FieldNumber::MEVSTATE:
          if(has_mevstate() && (::EmbeddedProto::Error::NO_ERRORS == return_value))
          {
            return_value = message_.mevstate_.serialize_with_id(static_cast<uint32_t>(FieldNumber::MEVSTATE), buffer, true);
          }
          break;

        default:
          break;
      }

      return return_value;
    };

    ::EmbeddedProto::Error deserialize(::EmbeddedProto::ReadBufferInterface& buffer) override
    {
      ::EmbeddedProto::Error return_value = ::EmbeddedProto::Error::NO_ERRORS;
      ::EmbeddedProto::WireFormatter::WireType wire_type = ::EmbeddedProto::WireFormatter::WireType::VARINT;
      uint32_t id_number = 0;
      FieldNumber id_tag = FieldNumber::NOT_SET;

      ::EmbeddedProto::Error tag_value = ::EmbeddedProto::WireFormatter::DeserializeTag(buffer, wire_type, id_number);
      while((::EmbeddedProto::Error::NO_ERRORS == return_value) && (::EmbeddedProto::Error::NO_ERRORS == tag_value))
      {
        id_tag = static_cast<FieldNumber>(id_number);
        switch(id_tag)
        {
          case FieldNumber::SOURCE:
            return_value = source_.deserialize_check_type(buffer, wire_type);
            break;

          case FieldNumber::TARGET:
            return_value = target_.deserialize_check_type(buffer, wire_type);
            break;

          case FieldNumber::MESSAGE_ID:
            return_value = message_id_.deserialize_check_type(buffer, wire_type);
            break;

          case FieldNumber::COORD:
          case FieldNumber::BARO:
          case FieldNumber::IMU:
          case FieldNumber::BAT:
          case FieldNumber::FLASHINFO:
          case FieldNumber::PRESSDMB:
          case FieldNumber::PRESSPBB:
          case FieldNumber::TEMPPBB:
          case FieldNumber::GPIO:
          case FieldNumber::PRESSRCU:
          case FieldNumber::TEMPRCU:
          case FieldNumber::NOS:
          case FieldNumber::RELAY:
          case FieldNumber::PADBOX:
          case FieldNumber::LR:
          case FieldNumber::TEMPSOB:
          case FieldNumber::IRTEMP:
          case FieldNumber::MEVSTATE:
            return_value = deserialize_message(id_tag, buffer, wire_type);
            break;

          case FieldNumber::NOT_SET:
            return_value = ::EmbeddedProto::Error::INVALID_FIELD_ID;
            break;

          default:
            return_value = skip_unknown_field(buffer, wire_type);
            break;
        }

        if(::EmbeddedProto::Error::NO_ERRORS == return_value)
        {
          // Read the next tag.
          tag_value = ::EmbeddedProto::WireFormatter::DeserializeTag(buffer, wire_type, id_number);
        }
      }

      // When an error was detect while reading the tag but no other errors where found, set it in the return value.
      if((::EmbeddedProto::Error::NO_ERRORS == return_value)
         && (::EmbeddedProto::Error::NO_ERRORS != tag_value)
         && (::EmbeddedProto::Error::END_OF_BUFFER != tag_value)) // The end of the buffer is not an array in this case.
      {
        return_value = tag_value;
      }

      return return_value;
    };

    void clear() override
    {
      clear_source();
      clear_target();
      clear_message_id();
      clear_message();

    }

    static char const* field_number_to_name(const FieldNumber fieldNumber)
    {
      char const* name = nullptr;
      switch(fieldNumber)
      {
        case FieldNumber::SOURCE:
          name = SOURCE_NAME;
          break;
        case FieldNumber::TARGET:
          name = TARGET_NAME;
          break;
        case FieldNumber::MESSAGE_ID:
          name = MESSAGE_ID_NAME;
          break;
        case FieldNumber::COORD:
          name = COORD_NAME;
          break;
        case FieldNumber::BARO:
          name = BARO_NAME;
          break;
        case FieldNumber::IMU:
          name = IMU_NAME;
          break;
        case FieldNumber::BAT:
          name = BAT_NAME;
          break;
        case FieldNumber::FLASHINFO:
          name = FLASHINFO_NAME;
          break;
        case FieldNumber::PRESSDMB:
          name = PRESSDMB_NAME;
          break;
        case FieldNumber::PRESSPBB:
          name = PRESSPBB_NAME;
          break;
        case FieldNumber::TEMPPBB:
          name = TEMPPBB_NAME;
          break;
        case FieldNumber::GPIO:
          name = GPIO_NAME;
          break;
        case FieldNumber::PRESSRCU:
          name = PRESSRCU_NAME;
          break;
        case FieldNumber::TEMPRCU:
          name = TEMPRCU_NAME;
          break;
        case FieldNumber::NOS:
          name = NOS_NAME;
          break;
        case FieldNumber::RELAY:
          name = RELAY_NAME;
          break;
        case FieldNumber::PADBOX:
          name = PADBOX_NAME;
          break;
        case FieldNumber::LR:
          name = LR_NAME;
          break;
        case FieldNumber::TEMPSOB:
          name = TEMPSOB_NAME;
          break;
        case FieldNumber::IRTEMP:
          name = IRTEMP_NAME;
          break;
        case FieldNumber::MEVSTATE:
          name = MEVSTATE_NAME;
          break;
        default:
          name = "Invalid FieldNumber";
          break;
      }
      return name;
    }

#ifdef MSG_TO_STRING

    ::EmbeddedProto::string_view to_string(::EmbeddedProto::string_view& str) const
    {
      return this->to_string(str, 0, nullptr, true);
    }

    ::EmbeddedProto::string_view to_string(::EmbeddedProto::string_view& str, const uint32_t indent_level, char const* name, const bool first_field) const override
    {
      ::EmbeddedProto::string_view left_chars = str;
      int32_t n_chars_used = 0;

      if(!first_field)
      {
        // Add a comma behind the previous field.
        n_chars_used = snprintf(left_chars.data, left_chars.size, ",\n");
        if(0 < n_chars_used)
        {
          // Update the character pointer and characters left in the array.
          left_chars.data += n_chars_used;
          left_chars.size -= n_chars_used;
        }
      }

      if(nullptr != name)
      {
        if( 0 == indent_level)
        {
          n_chars_used = snprintf(left_chars.data, left_chars.size, "\"%s\": {\n", name);
        }
        else
        {
          n_chars_used = snprintf(left_chars.data, left_chars.size, "%*s\"%s\": {\n", indent_level, " ", name);
        }
      }
      else
      {
        if( 0 == indent_level)
        {
          n_chars_used = snprintf(left_chars.data, left_chars.size, "{\n");
        }
        else
        {
          n_chars_used = snprintf(left_chars.data, left_chars.size, "%*s{\n", indent_level, " ");
        }
      }
      
      if(0 < n_chars_used)
      {
        left_chars.data += n_chars_used;
        left_chars.size -= n_chars_used;
      }

      left_chars = source_.to_string(left_chars, indent_level + 2, SOURCE_NAME, true);
      left_chars = target_.to_string(left_chars, indent_level + 2, TARGET_NAME, false);
      left_chars = message_id_.to_string(left_chars, indent_level + 2, MESSAGE_ID_NAME, false);
      left_chars = to_string_message(left_chars, indent_level + 2, false);
  
      if( 0 == indent_level) 
      {
        n_chars_used = snprintf(left_chars.data, left_chars.size, "\n}");
      }
      else 
      {
        n_chars_used = snprintf(left_chars.data, left_chars.size, "\n%*s}", indent_level, " ");
      }

      if(0 < n_chars_used)
      {
        left_chars.data += n_chars_used;
        left_chars.size -= n_chars_used;
      }

      return left_chars;
    }

#endif // End of MSG_TO_STRING

  private:


      EmbeddedProto::enumeration<Node> source_ = static_cast<Node>(0);
      EmbeddedProto::enumeration<Node> target_ = static_cast<Node>(0);
      EmbeddedProto::uint32 message_id_ = 0U;

      FieldNumber which_message_ = FieldNumber::NOT_SET;
      union message
      {
        message() {}
        ~message() {}
        GPS coord_;
        Baro baro_;
        IMU imu_;
        Battery bat_;
        Flash flashInfo_;
        DMBPressure pressdmb_;
        PBBPressure presspbb_;
        PBBTemp temppbb_;
        CombustionControlStatus gpio_;
        RCUPressure pressrcu_;
        RCUTemp temprcu_;
        NOSLoadCell nos_;
        RelayStatus relay_;
        PadBoxStatus padbox_;
        LRLoadCell lr_;
        SOBTemp tempsob_;
        IRTemperature irtemp_;
        MEVState mevstate_;
      };
      message message_;

      void init_message(const FieldNumber field_id)
      {
        if(FieldNumber::NOT_SET != which_message_)
        {
          // First delete the old object in the oneof.
          clear_message();
        }

        // C++11 unions only support nontrivial members when you explicitly call the placement new statement.
        switch(field_id)
        {
          case FieldNumber::COORD:
            new(&message_.coord_) GPS;
            break;

          case FieldNumber::BARO:
            new(&message_.baro_) Baro;
            break;

          case FieldNumber::IMU:
            new(&message_.imu_) IMU;
            break;

          case FieldNumber::BAT:
            new(&message_.bat_) Battery;
            break;

          case FieldNumber::FLASHINFO:
            new(&message_.flashInfo_) Flash;
            break;

          case FieldNumber::PRESSDMB:
            new(&message_.pressdmb_) DMBPressure;
            break;

          case FieldNumber::PRESSPBB:
            new(&message_.presspbb_) PBBPressure;
            break;

          case FieldNumber::TEMPPBB:
            new(&message_.temppbb_) PBBTemp;
            break;

          case FieldNumber::GPIO:
            new(&message_.gpio_) CombustionControlStatus;
            break;

          case FieldNumber::PRESSRCU:
            new(&message_.pressrcu_) RCUPressure;
            break;

          case FieldNumber::TEMPRCU:
            new(&message_.temprcu_) RCUTemp;
            break;

          case FieldNumber::NOS:
            new(&message_.nos_) NOSLoadCell;
            break;

          case FieldNumber::RELAY:
            new(&message_.relay_) RelayStatus;
            break;

          case FieldNumber::PADBOX:
            new(&message_.padbox_) PadBoxStatus;
            break;

          case FieldNumber::LR:
            new(&message_.lr_) LRLoadCell;
            break;

          case FieldNumber::TEMPSOB:
            new(&message_.tempsob_) SOBTemp;
            break;

          case FieldNumber::IRTEMP:
            new(&message_.irtemp_) IRTemperature;
            break;

          case FieldNumber::MEVSTATE:
            new(&message_.mevstate_) MEVState;
            break;

          default:
            break;
         }

         which_message_ = field_id;
      }

      void clear_message()
      {
        switch(which_message_)
        {
          case FieldNumber::COORD:
            ::EmbeddedProto::destroy_at(&message_.coord_);
            break;
          case FieldNumber::BARO:
            ::EmbeddedProto::destroy_at(&message_.baro_);
            break;
          case FieldNumber::IMU:
            ::EmbeddedProto::destroy_at(&message_.imu_);
            break;
          case FieldNumber::BAT:
            ::EmbeddedProto::destroy_at(&message_.bat_);
            break;
          case FieldNumber::FLASHINFO:
            ::EmbeddedProto::destroy_at(&message_.flashInfo_);
            break;
          case FieldNumber::PRESSDMB:
            ::EmbeddedProto::destroy_at(&message_.pressdmb_);
            break;
          case FieldNumber::PRESSPBB:
            ::EmbeddedProto::destroy_at(&message_.presspbb_);
            break;
          case FieldNumber::TEMPPBB:
            ::EmbeddedProto::destroy_at(&message_.temppbb_);
            break;
          case FieldNumber::GPIO:
            ::EmbeddedProto::destroy_at(&message_.gpio_);
            break;
          case FieldNumber::PRESSRCU:
            ::EmbeddedProto::destroy_at(&message_.pressrcu_);
            break;
          case FieldNumber::TEMPRCU:
            ::EmbeddedProto::destroy_at(&message_.temprcu_);
            break;
          case FieldNumber::NOS:
            ::EmbeddedProto::destroy_at(&message_.nos_);
            break;
          case FieldNumber::RELAY:
            ::EmbeddedProto::destroy_at(&message_.relay_);
            break;
          case FieldNumber::PADBOX:
            ::EmbeddedProto::destroy_at(&message_.padbox_);
            break;
          case FieldNumber::LR:
            ::EmbeddedProto::destroy_at(&message_.lr_);
            break;
          case FieldNumber::TEMPSOB:
            ::EmbeddedProto::destroy_at(&message_.tempsob_);
            break;
          case FieldNumber::IRTEMP:
            ::EmbeddedProto::destroy_at(&message_.irtemp_);
            break;
          case FieldNumber::MEVSTATE:
            ::EmbeddedProto::destroy_at(&message_.mevstate_);
            break;
          default:
            break;
        }
        which_message_ = FieldNumber::NOT_SET;
      }

      ::EmbeddedProto::Error deserialize_message(const FieldNumber field_id, 
                                    ::EmbeddedProto::ReadBufferInterface& buffer,
                                    const ::EmbeddedProto::WireFormatter::WireType wire_type)
      {
        ::EmbeddedProto::Error return_value = ::EmbeddedProto::Error::NO_ERRORS;
        
        if(field_id != which_message_)
        {
          init_message(field_id);
        }

        switch(which_message_)
        {
          case FieldNumber::COORD:
            return_value = message_.coord_.deserialize_check_type(buffer, wire_type);
            break;
          case FieldNumber::BARO:
            return_value = message_.baro_.deserialize_check_type(buffer, wire_type);
            break;
          case FieldNumber::IMU:
            return_value = message_.imu_.deserialize_check_type(buffer, wire_type);
            break;
          case FieldNumber::BAT:
            return_value = message_.bat_.deserialize_check_type(buffer, wire_type);
            break;
          case FieldNumber::FLASHINFO:
            return_value = message_.flashInfo_.deserialize_check_type(buffer, wire_type);
            break;
          case FieldNumber::PRESSDMB:
            return_value = message_.pressdmb_.deserialize_check_type(buffer, wire_type);
            break;
          case FieldNumber::PRESSPBB:
            return_value = message_.presspbb_.deserialize_check_type(buffer, wire_type);
            break;
          case FieldNumber::TEMPPBB:
            return_value = message_.temppbb_.deserialize_check_type(buffer, wire_type);
            break;
          case FieldNumber::GPIO:
            return_value = message_.gpio_.deserialize_check_type(buffer, wire_type);
            break;
          case FieldNumber::PRESSRCU:
            return_value = message_.pressrcu_.deserialize_check_type(buffer, wire_type);
            break;
          case FieldNumber::TEMPRCU:
            return_value = message_.temprcu_.deserialize_check_type(buffer, wire_type);
            break;
          case FieldNumber::NOS:
            return_value = message_.nos_.deserialize_check_type(buffer, wire_type);
            break;
          case FieldNumber::RELAY:
            return_value = message_.relay_.deserialize_check_type(buffer, wire_type);
            break;
          case FieldNumber::PADBOX:
            return_value = message_.padbox_.deserialize_check_type(buffer, wire_type);
            break;
          case FieldNumber::LR:
            return_value = message_.lr_.deserialize_check_type(buffer, wire_type);
            break;
          case FieldNumber::TEMPSOB:
            return_value = message_.tempsob_.deserialize_check_type(buffer, wire_type);
            break;
          case FieldNumber::IRTEMP:
            return_value = message_.irtemp_.deserialize_check_type(buffer, wire_type);
            break;
          case FieldNumber::MEVSTATE:
            return_value = message_.mevstate_.deserialize_check_type(buffer, wire_type);
            break;
          default:
            break;
        }

        if(::EmbeddedProto::Error::NO_ERRORS != return_value)
        {
          clear_message();
        }
        return return_value;
      }

#ifdef MSG_TO_STRING 
      ::EmbeddedProto::string_view to_string_message(::EmbeddedProto::string_view& str, const uint32_t indent_level, const bool first_field) const
      {
        ::EmbeddedProto::string_view left_chars = str;

        switch(which_message_)
        {
          case FieldNumber::COORD:
            left_chars = message_.coord_.to_string(left_chars, indent_level, COORD_NAME, first_field);
            break;
          case FieldNumber::BARO:
            left_chars = message_.baro_.to_string(left_chars, indent_level, BARO_NAME, first_field);
            break;
          case FieldNumber::IMU:
            left_chars = message_.imu_.to_string(left_chars, indent_level, IMU_NAME, first_field);
            break;
          case FieldNumber::BAT:
            left_chars = message_.bat_.to_string(left_chars, indent_level, BAT_NAME, first_field);
            break;
          case FieldNumber::FLASHINFO:
            left_chars = message_.flashInfo_.to_string(left_chars, indent_level, FLASHINFO_NAME, first_field);
            break;
          case FieldNumber::PRESSDMB:
            left_chars = message_.pressdmb_.to_string(left_chars, indent_level, PRESSDMB_NAME, first_field);
            break;
          case FieldNumber::PRESSPBB:
            left_chars = message_.presspbb_.to_string(left_chars, indent_level, PRESSPBB_NAME, first_field);
            break;
          case FieldNumber::TEMPPBB:
            left_chars = message_.temppbb_.to_string(left_chars, indent_level, TEMPPBB_NAME, first_field);
            break;
          case FieldNumber::GPIO:
            left_chars = message_.gpio_.to_string(left_chars, indent_level, GPIO_NAME, first_field);
            break;
          case FieldNumber::PRESSRCU:
            left_chars = message_.pressrcu_.to_string(left_chars, indent_level, PRESSRCU_NAME, first_field);
            break;
          case FieldNumber::TEMPRCU:
            left_chars = message_.temprcu_.to_string(left_chars, indent_level, TEMPRCU_NAME, first_field);
            break;
          case FieldNumber::NOS:
            left_chars = message_.nos_.to_string(left_chars, indent_level, NOS_NAME, first_field);
            break;
          case FieldNumber::RELAY:
            left_chars = message_.relay_.to_string(left_chars, indent_level, RELAY_NAME, first_field);
            break;
          case FieldNumber::PADBOX:
            left_chars = message_.padbox_.to_string(left_chars, indent_level, PADBOX_NAME, first_field);
            break;
          case FieldNumber::LR:
            left_chars = message_.lr_.to_string(left_chars, indent_level, LR_NAME, first_field);
            break;
          case FieldNumber::TEMPSOB:
            left_chars = message_.tempsob_.to_string(left_chars, indent_level, TEMPSOB_NAME, first_field);
            break;
          case FieldNumber::IRTEMP:
            left_chars = message_.irtemp_.to_string(left_chars, indent_level, IRTEMP_NAME, first_field);
            break;
          case FieldNumber::MEVSTATE:
            left_chars = message_.mevstate_.to_string(left_chars, indent_level, MEVSTATE_NAME, first_field);
            break;
          default:
            break;
        }

        return left_chars;
      }

#endif // End of MSG_TO_STRING
};

} // End of namespace Proto
#endif // TELEMETRYMESSAGE_H