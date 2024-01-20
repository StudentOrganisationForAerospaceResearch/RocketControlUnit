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
#ifndef CONTROLMESSAGE_H
#define CONTROLMESSAGE_H

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

class AckNack final: public ::EmbeddedProto::MessageInterface
{
  public:
    AckNack() = default;
    AckNack(const AckNack& rhs )
    {
      set_acking_msg_source(rhs.get_acking_msg_source());
      set_acking_msg_id(rhs.get_acking_msg_id());
      set_acking_sequence_num(rhs.get_acking_sequence_num());
    }

    AckNack(const AckNack&& rhs ) noexcept
    {
      set_acking_msg_source(rhs.get_acking_msg_source());
      set_acking_msg_id(rhs.get_acking_msg_id());
      set_acking_sequence_num(rhs.get_acking_sequence_num());
    }

    ~AckNack() override = default;

    enum class FieldNumber : uint32_t
    {
      NOT_SET = 0,
      ACKING_MSG_SOURCE = 1,
      ACKING_MSG_ID = 2,
      ACKING_SEQUENCE_NUM = 3
    };

    AckNack& operator=(const AckNack& rhs)
    {
      set_acking_msg_source(rhs.get_acking_msg_source());
      set_acking_msg_id(rhs.get_acking_msg_id());
      set_acking_sequence_num(rhs.get_acking_sequence_num());
      return *this;
    }

    AckNack& operator=(const AckNack&& rhs) noexcept
    {
      set_acking_msg_source(rhs.get_acking_msg_source());
      set_acking_msg_id(rhs.get_acking_msg_id());
      set_acking_sequence_num(rhs.get_acking_sequence_num());
      return *this;
    }

    static constexpr char const* ACKING_MSG_SOURCE_NAME = "acking_msg_source";
    inline void clear_acking_msg_source() { acking_msg_source_.clear(); }
    inline void set_acking_msg_source(const Node& value) { acking_msg_source_ = value; }
    inline void set_acking_msg_source(const Node&& value) { acking_msg_source_ = value; }
    inline const Node& get_acking_msg_source() const { return acking_msg_source_.get(); }
    inline Node acking_msg_source() const { return acking_msg_source_.get(); }

    static constexpr char const* ACKING_MSG_ID_NAME = "acking_msg_id";
    inline void clear_acking_msg_id() { acking_msg_id_.clear(); }
    inline void set_acking_msg_id(const MessageID& value) { acking_msg_id_ = value; }
    inline void set_acking_msg_id(const MessageID&& value) { acking_msg_id_ = value; }
    inline const MessageID& get_acking_msg_id() const { return acking_msg_id_.get(); }
    inline MessageID acking_msg_id() const { return acking_msg_id_.get(); }

    static constexpr char const* ACKING_SEQUENCE_NUM_NAME = "acking_sequence_num";
    inline void clear_acking_sequence_num() { acking_sequence_num_.clear(); }
    inline void set_acking_sequence_num(const uint32_t& value) { acking_sequence_num_ = value; }
    inline void set_acking_sequence_num(const uint32_t&& value) { acking_sequence_num_ = value; }
    inline uint32_t& mutable_acking_sequence_num() { return acking_sequence_num_.get(); }
    inline const uint32_t& get_acking_sequence_num() const { return acking_sequence_num_.get(); }
    inline uint32_t acking_sequence_num() const { return acking_sequence_num_.get(); }


    ::EmbeddedProto::Error serialize(::EmbeddedProto::WriteBufferInterface& buffer) const override
    {
      ::EmbeddedProto::Error return_value = ::EmbeddedProto::Error::NO_ERRORS;

      if((static_cast<Node>(0) != acking_msg_source_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = acking_msg_source_.serialize_with_id(static_cast<uint32_t>(FieldNumber::ACKING_MSG_SOURCE), buffer, false);
      }

      if((static_cast<MessageID>(0) != acking_msg_id_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = acking_msg_id_.serialize_with_id(static_cast<uint32_t>(FieldNumber::ACKING_MSG_ID), buffer, false);
      }

      if((0U != acking_sequence_num_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = acking_sequence_num_.serialize_with_id(static_cast<uint32_t>(FieldNumber::ACKING_SEQUENCE_NUM), buffer, false);
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
          case FieldNumber::ACKING_MSG_SOURCE:
            return_value = acking_msg_source_.deserialize_check_type(buffer, wire_type);
            break;

          case FieldNumber::ACKING_MSG_ID:
            return_value = acking_msg_id_.deserialize_check_type(buffer, wire_type);
            break;

          case FieldNumber::ACKING_SEQUENCE_NUM:
            return_value = acking_sequence_num_.deserialize_check_type(buffer, wire_type);
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
      clear_acking_msg_source();
      clear_acking_msg_id();
      clear_acking_sequence_num();

    }

    static char const* field_number_to_name(const FieldNumber fieldNumber)
    {
      char const* name = nullptr;
      switch(fieldNumber)
      {
        case FieldNumber::ACKING_MSG_SOURCE:
          name = ACKING_MSG_SOURCE_NAME;
          break;
        case FieldNumber::ACKING_MSG_ID:
          name = ACKING_MSG_ID_NAME;
          break;
        case FieldNumber::ACKING_SEQUENCE_NUM:
          name = ACKING_SEQUENCE_NUM_NAME;
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

      left_chars = acking_msg_source_.to_string(left_chars, indent_level + 2, ACKING_MSG_SOURCE_NAME, true);
      left_chars = acking_msg_id_.to_string(left_chars, indent_level + 2, ACKING_MSG_ID_NAME, false);
      left_chars = acking_sequence_num_.to_string(left_chars, indent_level + 2, ACKING_SEQUENCE_NUM_NAME, false);
  
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


      EmbeddedProto::enumeration<Node> acking_msg_source_ = static_cast<Node>(0);
      EmbeddedProto::enumeration<MessageID> acking_msg_id_ = static_cast<MessageID>(0);
      EmbeddedProto::uint32 acking_sequence_num_ = 0U;

};

class Heartbeat final: public ::EmbeddedProto::MessageInterface
{
  public:
    Heartbeat() = default;
    Heartbeat(const Heartbeat& rhs )
    {
      set_hb_response_sequence_num(rhs.get_hb_response_sequence_num());
    }

    Heartbeat(const Heartbeat&& rhs ) noexcept
    {
      set_hb_response_sequence_num(rhs.get_hb_response_sequence_num());
    }

    ~Heartbeat() override = default;

    enum class FieldNumber : uint32_t
    {
      NOT_SET = 0,
      HB_RESPONSE_SEQUENCE_NUM = 1
    };

    Heartbeat& operator=(const Heartbeat& rhs)
    {
      set_hb_response_sequence_num(rhs.get_hb_response_sequence_num());
      return *this;
    }

    Heartbeat& operator=(const Heartbeat&& rhs) noexcept
    {
      set_hb_response_sequence_num(rhs.get_hb_response_sequence_num());
      return *this;
    }

    static constexpr char const* HB_RESPONSE_SEQUENCE_NUM_NAME = "hb_response_sequence_num";
    inline void clear_hb_response_sequence_num() { hb_response_sequence_num_.clear(); }
    inline void set_hb_response_sequence_num(const uint32_t& value) { hb_response_sequence_num_ = value; }
    inline void set_hb_response_sequence_num(const uint32_t&& value) { hb_response_sequence_num_ = value; }
    inline uint32_t& mutable_hb_response_sequence_num() { return hb_response_sequence_num_.get(); }
    inline const uint32_t& get_hb_response_sequence_num() const { return hb_response_sequence_num_.get(); }
    inline uint32_t hb_response_sequence_num() const { return hb_response_sequence_num_.get(); }


    ::EmbeddedProto::Error serialize(::EmbeddedProto::WriteBufferInterface& buffer) const override
    {
      ::EmbeddedProto::Error return_value = ::EmbeddedProto::Error::NO_ERRORS;

      if((0U != hb_response_sequence_num_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = hb_response_sequence_num_.serialize_with_id(static_cast<uint32_t>(FieldNumber::HB_RESPONSE_SEQUENCE_NUM), buffer, false);
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
          case FieldNumber::HB_RESPONSE_SEQUENCE_NUM:
            return_value = hb_response_sequence_num_.deserialize_check_type(buffer, wire_type);
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
      clear_hb_response_sequence_num();

    }

    static char const* field_number_to_name(const FieldNumber fieldNumber)
    {
      char const* name = nullptr;
      switch(fieldNumber)
      {
        case FieldNumber::HB_RESPONSE_SEQUENCE_NUM:
          name = HB_RESPONSE_SEQUENCE_NUM_NAME;
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

      left_chars = hb_response_sequence_num_.to_string(left_chars, indent_level + 2, HB_RESPONSE_SEQUENCE_NUM_NAME, true);
  
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


      EmbeddedProto::uint32 hb_response_sequence_num_ = 0U;

};

class Ping final: public ::EmbeddedProto::MessageInterface
{
  public:
    Ping() = default;
    Ping(const Ping& rhs )
    {
      set_ping_ack_id(rhs.get_ping_ack_id());
      set_ping_response_sequence_num(rhs.get_ping_response_sequence_num());
      set_sys_state_response_required(rhs.get_sys_state_response_required());
    }

    Ping(const Ping&& rhs ) noexcept
    {
      set_ping_ack_id(rhs.get_ping_ack_id());
      set_ping_response_sequence_num(rhs.get_ping_response_sequence_num());
      set_sys_state_response_required(rhs.get_sys_state_response_required());
    }

    ~Ping() override = default;

    enum class FieldNumber : uint32_t
    {
      NOT_SET = 0,
      PING_ACK_ID = 1,
      PING_RESPONSE_SEQUENCE_NUM = 2,
      SYS_STATE_RESPONSE_REQUIRED = 3
    };

    Ping& operator=(const Ping& rhs)
    {
      set_ping_ack_id(rhs.get_ping_ack_id());
      set_ping_response_sequence_num(rhs.get_ping_response_sequence_num());
      set_sys_state_response_required(rhs.get_sys_state_response_required());
      return *this;
    }

    Ping& operator=(const Ping&& rhs) noexcept
    {
      set_ping_ack_id(rhs.get_ping_ack_id());
      set_ping_response_sequence_num(rhs.get_ping_response_sequence_num());
      set_sys_state_response_required(rhs.get_sys_state_response_required());
      return *this;
    }

    static constexpr char const* PING_ACK_ID_NAME = "ping_ack_id";
    inline void clear_ping_ack_id() { ping_ack_id_.clear(); }
    inline void set_ping_ack_id(const uint32_t& value) { ping_ack_id_ = value; }
    inline void set_ping_ack_id(const uint32_t&& value) { ping_ack_id_ = value; }
    inline uint32_t& mutable_ping_ack_id() { return ping_ack_id_.get(); }
    inline const uint32_t& get_ping_ack_id() const { return ping_ack_id_.get(); }
    inline uint32_t ping_ack_id() const { return ping_ack_id_.get(); }

    static constexpr char const* PING_RESPONSE_SEQUENCE_NUM_NAME = "ping_response_sequence_num";
    inline void clear_ping_response_sequence_num() { ping_response_sequence_num_.clear(); }
    inline void set_ping_response_sequence_num(const uint32_t& value) { ping_response_sequence_num_ = value; }
    inline void set_ping_response_sequence_num(const uint32_t&& value) { ping_response_sequence_num_ = value; }
    inline uint32_t& mutable_ping_response_sequence_num() { return ping_response_sequence_num_.get(); }
    inline const uint32_t& get_ping_response_sequence_num() const { return ping_response_sequence_num_.get(); }
    inline uint32_t ping_response_sequence_num() const { return ping_response_sequence_num_.get(); }

    static constexpr char const* SYS_STATE_RESPONSE_REQUIRED_NAME = "sys_state_response_required";
    inline void clear_sys_state_response_required() { sys_state_response_required_.clear(); }
    inline void set_sys_state_response_required(const bool& value) { sys_state_response_required_ = value; }
    inline void set_sys_state_response_required(const bool&& value) { sys_state_response_required_ = value; }
    inline bool& mutable_sys_state_response_required() { return sys_state_response_required_.get(); }
    inline const bool& get_sys_state_response_required() const { return sys_state_response_required_.get(); }
    inline bool sys_state_response_required() const { return sys_state_response_required_.get(); }


    ::EmbeddedProto::Error serialize(::EmbeddedProto::WriteBufferInterface& buffer) const override
    {
      ::EmbeddedProto::Error return_value = ::EmbeddedProto::Error::NO_ERRORS;

      if((0U != ping_ack_id_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = ping_ack_id_.serialize_with_id(static_cast<uint32_t>(FieldNumber::PING_ACK_ID), buffer, false);
      }

      if((0U != ping_response_sequence_num_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = ping_response_sequence_num_.serialize_with_id(static_cast<uint32_t>(FieldNumber::PING_RESPONSE_SEQUENCE_NUM), buffer, false);
      }

      if((false != sys_state_response_required_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = sys_state_response_required_.serialize_with_id(static_cast<uint32_t>(FieldNumber::SYS_STATE_RESPONSE_REQUIRED), buffer, false);
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
          case FieldNumber::PING_ACK_ID:
            return_value = ping_ack_id_.deserialize_check_type(buffer, wire_type);
            break;

          case FieldNumber::PING_RESPONSE_SEQUENCE_NUM:
            return_value = ping_response_sequence_num_.deserialize_check_type(buffer, wire_type);
            break;

          case FieldNumber::SYS_STATE_RESPONSE_REQUIRED:
            return_value = sys_state_response_required_.deserialize_check_type(buffer, wire_type);
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
      clear_ping_ack_id();
      clear_ping_response_sequence_num();
      clear_sys_state_response_required();

    }

    static char const* field_number_to_name(const FieldNumber fieldNumber)
    {
      char const* name = nullptr;
      switch(fieldNumber)
      {
        case FieldNumber::PING_ACK_ID:
          name = PING_ACK_ID_NAME;
          break;
        case FieldNumber::PING_RESPONSE_SEQUENCE_NUM:
          name = PING_RESPONSE_SEQUENCE_NUM_NAME;
          break;
        case FieldNumber::SYS_STATE_RESPONSE_REQUIRED:
          name = SYS_STATE_RESPONSE_REQUIRED_NAME;
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

      left_chars = ping_ack_id_.to_string(left_chars, indent_level + 2, PING_ACK_ID_NAME, true);
      left_chars = ping_response_sequence_num_.to_string(left_chars, indent_level + 2, PING_RESPONSE_SEQUENCE_NUM_NAME, false);
      left_chars = sys_state_response_required_.to_string(left_chars, indent_level + 2, SYS_STATE_RESPONSE_REQUIRED_NAME, false);
  
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


      EmbeddedProto::uint32 ping_ack_id_ = 0U;
      EmbeddedProto::uint32 ping_response_sequence_num_ = 0U;
      EmbeddedProto::boolean sys_state_response_required_ = false;

};

class SystemControl final: public ::EmbeddedProto::MessageInterface
{
  public:
    SystemControl() = default;
    SystemControl(const SystemControl& rhs )
    {
      set_sys_cmd(rhs.get_sys_cmd());
      set_cmd_param(rhs.get_cmd_param());
    }

    SystemControl(const SystemControl&& rhs ) noexcept
    {
      set_sys_cmd(rhs.get_sys_cmd());
      set_cmd_param(rhs.get_cmd_param());
    }

    ~SystemControl() override = default;

    enum class Command : uint32_t
    {
      SYS_INVALID = 0,
      SYS_RESET = 1,
      SYS_FLASH_ERASE = 2,
      SYS_LOG_PERIOD_CHANGE = 3,
      HEARTBEAT_ENABLE = 4,
      HEARTBEAT_DISABLE = 5,
      SYS_FLASH_LOG_ENABLE = 6,
      SYS_FLASH_LOG_DISABLE = 7,
      SYS_CRITICAL_FLASH_FULL_ERASE = 8
    };

    enum class FieldNumber : uint32_t
    {
      NOT_SET = 0,
      SYS_CMD = 1,
      CMD_PARAM = 2
    };

    SystemControl& operator=(const SystemControl& rhs)
    {
      set_sys_cmd(rhs.get_sys_cmd());
      set_cmd_param(rhs.get_cmd_param());
      return *this;
    }

    SystemControl& operator=(const SystemControl&& rhs) noexcept
    {
      set_sys_cmd(rhs.get_sys_cmd());
      set_cmd_param(rhs.get_cmd_param());
      return *this;
    }

    static constexpr char const* SYS_CMD_NAME = "sys_cmd";
    inline void clear_sys_cmd() { sys_cmd_.clear(); }
    inline void set_sys_cmd(const Command& value) { sys_cmd_ = value; }
    inline void set_sys_cmd(const Command&& value) { sys_cmd_ = value; }
    inline const Command& get_sys_cmd() const { return sys_cmd_.get(); }
    inline Command sys_cmd() const { return sys_cmd_.get(); }

    static constexpr char const* CMD_PARAM_NAME = "cmd_param";
    inline void clear_cmd_param() { cmd_param_.clear(); }
    inline void set_cmd_param(const uint32_t& value) { cmd_param_ = value; }
    inline void set_cmd_param(const uint32_t&& value) { cmd_param_ = value; }
    inline uint32_t& mutable_cmd_param() { return cmd_param_.get(); }
    inline const uint32_t& get_cmd_param() const { return cmd_param_.get(); }
    inline uint32_t cmd_param() const { return cmd_param_.get(); }


    ::EmbeddedProto::Error serialize(::EmbeddedProto::WriteBufferInterface& buffer) const override
    {
      ::EmbeddedProto::Error return_value = ::EmbeddedProto::Error::NO_ERRORS;

      if((static_cast<Command>(0) != sys_cmd_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = sys_cmd_.serialize_with_id(static_cast<uint32_t>(FieldNumber::SYS_CMD), buffer, false);
      }

      if((0U != cmd_param_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = cmd_param_.serialize_with_id(static_cast<uint32_t>(FieldNumber::CMD_PARAM), buffer, false);
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
          case FieldNumber::SYS_CMD:
            return_value = sys_cmd_.deserialize_check_type(buffer, wire_type);
            break;

          case FieldNumber::CMD_PARAM:
            return_value = cmd_param_.deserialize_check_type(buffer, wire_type);
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
      clear_sys_cmd();
      clear_cmd_param();

    }

    static char const* field_number_to_name(const FieldNumber fieldNumber)
    {
      char const* name = nullptr;
      switch(fieldNumber)
      {
        case FieldNumber::SYS_CMD:
          name = SYS_CMD_NAME;
          break;
        case FieldNumber::CMD_PARAM:
          name = CMD_PARAM_NAME;
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

      left_chars = sys_cmd_.to_string(left_chars, indent_level + 2, SYS_CMD_NAME, true);
      left_chars = cmd_param_.to_string(left_chars, indent_level + 2, CMD_PARAM_NAME, false);
  
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


      EmbeddedProto::enumeration<Command> sys_cmd_ = static_cast<Command>(0);
      EmbeddedProto::uint32 cmd_param_ = 0U;

};

class SystemState final: public ::EmbeddedProto::MessageInterface
{
  public:
    SystemState() = default;
    SystemState(const SystemState& rhs )
    {
      set_sys_state(rhs.get_sys_state());
      if(rhs.has_rocket_state())
      {
        set_rocket_state(rhs.get_rocket_state());
      }
      else
      {
        clear_rocket_state();
      }

    }

    SystemState(const SystemState&& rhs ) noexcept
    {
      set_sys_state(rhs.get_sys_state());
      if(rhs.has_rocket_state())
      {
        set_rocket_state(rhs.get_rocket_state());
      }
      else
      {
        clear_rocket_state();
      }

    }

    ~SystemState() override = default;

    enum class State : uint32_t
    {
      SYS_INVALID = 0,
      SYS_BOOTUP_COMPLETE = 1,
      SYS_ASSERT_FAILURE_RESET = 2,
      SYS_UNCAUGHT_RESET = 3,
      SYS_NORMAL_OPERATION = 4,
      SYS_HEARTBEAT_LOSS_HALF_WARNING = 5,
      SYS_HEARTBEAT_LOST_ABORTING = 6
    };

    enum class FieldNumber : uint32_t
    {
      NOT_SET = 0,
      SYS_STATE = 1,
      ROCKET_STATE = 2
    };

    SystemState& operator=(const SystemState& rhs)
    {
      set_sys_state(rhs.get_sys_state());
      if(rhs.has_rocket_state())
      {
        set_rocket_state(rhs.get_rocket_state());
      }
      else
      {
        clear_rocket_state();
      }

      return *this;
    }

    SystemState& operator=(const SystemState&& rhs) noexcept
    {
      set_sys_state(rhs.get_sys_state());
      if(rhs.has_rocket_state())
      {
        set_rocket_state(rhs.get_rocket_state());
      }
      else
      {
        clear_rocket_state();
      }
      
      return *this;
    }

    static constexpr char const* SYS_STATE_NAME = "sys_state";
    inline void clear_sys_state() { sys_state_.clear(); }
    inline void set_sys_state(const State& value) { sys_state_ = value; }
    inline void set_sys_state(const State&& value) { sys_state_ = value; }
    inline const State& get_sys_state() const { return sys_state_.get(); }
    inline State sys_state() const { return sys_state_.get(); }

    static constexpr char const* ROCKET_STATE_NAME = "rocket_state";
    inline bool has_rocket_state() const
    {
      return 0 != (presence::mask(presence::fields::ROCKET_STATE) & presence_[presence::index(presence::fields::ROCKET_STATE)]);
    }
    inline void clear_rocket_state()
    {
      presence_[presence::index(presence::fields::ROCKET_STATE)] &= ~(presence::mask(presence::fields::ROCKET_STATE));
      rocket_state_.clear();
    }
    inline void set_rocket_state(const RocketState& value)
    {
      presence_[presence::index(presence::fields::ROCKET_STATE)] |= presence::mask(presence::fields::ROCKET_STATE);
      rocket_state_ = value;
    }
    inline void set_rocket_state(const RocketState&& value)
    {
      presence_[presence::index(presence::fields::ROCKET_STATE)] |= presence::mask(presence::fields::ROCKET_STATE);
      rocket_state_ = value;
    }
    inline const RocketState& get_rocket_state() const { return rocket_state_.get(); }
    inline RocketState rocket_state() const { return rocket_state_.get(); }


    ::EmbeddedProto::Error serialize(::EmbeddedProto::WriteBufferInterface& buffer) const override
    {
      ::EmbeddedProto::Error return_value = ::EmbeddedProto::Error::NO_ERRORS;

      if((static_cast<State>(0) != sys_state_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = sys_state_.serialize_with_id(static_cast<uint32_t>(FieldNumber::SYS_STATE), buffer, false);
      }

      if(has_rocket_state() && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = rocket_state_.serialize_with_id(static_cast<uint32_t>(FieldNumber::ROCKET_STATE), buffer, true);
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
          case FieldNumber::SYS_STATE:
            return_value = sys_state_.deserialize_check_type(buffer, wire_type);
            break;

          case FieldNumber::ROCKET_STATE:
            presence_[presence::index(presence::fields::ROCKET_STATE)] |= presence::mask(presence::fields::ROCKET_STATE);
            return_value = rocket_state_.deserialize_check_type(buffer, wire_type);
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
      clear_sys_state();
      clear_rocket_state();

    }

    static char const* field_number_to_name(const FieldNumber fieldNumber)
    {
      char const* name = nullptr;
      switch(fieldNumber)
      {
        case FieldNumber::SYS_STATE:
          name = SYS_STATE_NAME;
          break;
        case FieldNumber::ROCKET_STATE:
          name = ROCKET_STATE_NAME;
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

      left_chars = sys_state_.to_string(left_chars, indent_level + 2, SYS_STATE_NAME, true);
      left_chars = rocket_state_.to_string(left_chars, indent_level + 2, ROCKET_STATE_NAME, false);
  
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

      // Define constants for tracking the presence of fields.
      // Use a struct to scope the variables from user fields as namespaces are not allowed within classes.
      struct presence
      {
        // An enumeration with all the fields for which presence has to be tracked.
        enum class fields : uint32_t
        {
          ROCKET_STATE
        };

        // The number of fields for which presence has to be tracked.
        static constexpr uint32_t N_FIELDS = 1;

        // Which type are we using to track presence.
        using TYPE = uint32_t;

        // How many bits are there in the presence type.
        static constexpr uint32_t N_BITS = std::numeric_limits<TYPE>::digits;

        // How many variables of TYPE do we need to bit mask all presence fields.
        static constexpr uint32_t SIZE = (N_FIELDS / N_BITS) + ((N_FIELDS % N_BITS) > 0 ? 1 : 0);

        // Obtain the index of a given field in the presence array.
        static constexpr uint32_t index(const fields& field) { return static_cast<uint32_t>(field) / N_BITS; }

        // Obtain the bit mask for the given field assuming we are at the correct index in the presence array.
        static constexpr TYPE mask(const fields& field)
        {
          return static_cast<uint32_t>(0x01) << (static_cast<uint32_t>(field) % N_BITS);
        }
      };

      // Create an array in which the presence flags are stored.
      typename presence::TYPE presence_[presence::SIZE] = {0};

      EmbeddedProto::enumeration<State> sys_state_ = static_cast<State>(0);
      EmbeddedProto::enumeration<RocketState> rocket_state_ = static_cast<RocketState>(0);

};

class ControlMessage final: public ::EmbeddedProto::MessageInterface
{
  public:
    ControlMessage() = default;
    ControlMessage(const ControlMessage& rhs )
    {
      set_source(rhs.get_source());
      set_target(rhs.get_target());
      set_message_id(rhs.get_message_id());
      set_source_sequence_num(rhs.get_source_sequence_num());
      if(rhs.get_which_message() != which_message_)
      {
        // First delete the old object in the oneof.
        clear_message();
      }

      switch(rhs.get_which_message())
      {
        case FieldNumber::ACK:
          set_ack(rhs.get_ack());
          break;

        case FieldNumber::NACK:
          set_nack(rhs.get_nack());
          break;

        case FieldNumber::PING:
          set_ping(rhs.get_ping());
          break;

        case FieldNumber::HB:
          set_hb(rhs.get_hb());
          break;

        case FieldNumber::SYS_STATE:
          set_sys_state(rhs.get_sys_state());
          break;

        case FieldNumber::SYS_CTRL:
          set_sys_ctrl(rhs.get_sys_ctrl());
          break;

        default:
          break;
      }

    }

    ControlMessage(const ControlMessage&& rhs ) noexcept
    {
      set_source(rhs.get_source());
      set_target(rhs.get_target());
      set_message_id(rhs.get_message_id());
      set_source_sequence_num(rhs.get_source_sequence_num());
      if(rhs.get_which_message() != which_message_)
      {
        // First delete the old object in the oneof.
        clear_message();
      }

      switch(rhs.get_which_message())
      {
        case FieldNumber::ACK:
          set_ack(rhs.get_ack());
          break;

        case FieldNumber::NACK:
          set_nack(rhs.get_nack());
          break;

        case FieldNumber::PING:
          set_ping(rhs.get_ping());
          break;

        case FieldNumber::HB:
          set_hb(rhs.get_hb());
          break;

        case FieldNumber::SYS_STATE:
          set_sys_state(rhs.get_sys_state());
          break;

        case FieldNumber::SYS_CTRL:
          set_sys_ctrl(rhs.get_sys_ctrl());
          break;

        default:
          break;
      }

    }

    ~ControlMessage() override = default;

    enum class FieldNumber : uint32_t
    {
      NOT_SET = 0,
      SOURCE = 1,
      TARGET = 2,
      MESSAGE_ID = 3,
      SOURCE_SEQUENCE_NUM = 4,
      ACK = 5,
      NACK = 6,
      PING = 7,
      HB = 8,
      SYS_STATE = 9,
      SYS_CTRL = 10
    };

    ControlMessage& operator=(const ControlMessage& rhs)
    {
      set_source(rhs.get_source());
      set_target(rhs.get_target());
      set_message_id(rhs.get_message_id());
      set_source_sequence_num(rhs.get_source_sequence_num());
      if(rhs.get_which_message() != which_message_)
      {
        // First delete the old object in the oneof.
        clear_message();
      }

      switch(rhs.get_which_message())
      {
        case FieldNumber::ACK:
          set_ack(rhs.get_ack());
          break;

        case FieldNumber::NACK:
          set_nack(rhs.get_nack());
          break;

        case FieldNumber::PING:
          set_ping(rhs.get_ping());
          break;

        case FieldNumber::HB:
          set_hb(rhs.get_hb());
          break;

        case FieldNumber::SYS_STATE:
          set_sys_state(rhs.get_sys_state());
          break;

        case FieldNumber::SYS_CTRL:
          set_sys_ctrl(rhs.get_sys_ctrl());
          break;

        default:
          break;
      }

      return *this;
    }

    ControlMessage& operator=(const ControlMessage&& rhs) noexcept
    {
      set_source(rhs.get_source());
      set_target(rhs.get_target());
      set_message_id(rhs.get_message_id());
      set_source_sequence_num(rhs.get_source_sequence_num());
      if(rhs.get_which_message() != which_message_)
      {
        // First delete the old object in the oneof.
        clear_message();
      }

      switch(rhs.get_which_message())
      {
        case FieldNumber::ACK:
          set_ack(rhs.get_ack());
          break;

        case FieldNumber::NACK:
          set_nack(rhs.get_nack());
          break;

        case FieldNumber::PING:
          set_ping(rhs.get_ping());
          break;

        case FieldNumber::HB:
          set_hb(rhs.get_hb());
          break;

        case FieldNumber::SYS_STATE:
          set_sys_state(rhs.get_sys_state());
          break;

        case FieldNumber::SYS_CTRL:
          set_sys_ctrl(rhs.get_sys_ctrl());
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
    inline void set_message_id(const MessageID& value) { message_id_ = value; }
    inline void set_message_id(const MessageID&& value) { message_id_ = value; }
    inline const MessageID& get_message_id() const { return message_id_.get(); }
    inline MessageID message_id() const { return message_id_.get(); }

    static constexpr char const* SOURCE_SEQUENCE_NUM_NAME = "source_sequence_num";
    inline void clear_source_sequence_num() { source_sequence_num_.clear(); }
    inline void set_source_sequence_num(const uint32_t& value) { source_sequence_num_ = value; }
    inline void set_source_sequence_num(const uint32_t&& value) { source_sequence_num_ = value; }
    inline uint32_t& mutable_source_sequence_num() { return source_sequence_num_.get(); }
    inline const uint32_t& get_source_sequence_num() const { return source_sequence_num_.get(); }
    inline uint32_t source_sequence_num() const { return source_sequence_num_.get(); }

    FieldNumber get_which_message() const { return which_message_; }

    static constexpr char const* ACK_NAME = "ack";
    inline bool has_ack() const
    {
      return FieldNumber::ACK == which_message_;
    }
    inline void clear_ack()
    {
      if(FieldNumber::ACK == which_message_)
      {
        which_message_ = FieldNumber::NOT_SET;
        message_.ack_.~AckNack();
      }
    }
    inline void set_ack(const AckNack& value)
    {
      if(FieldNumber::ACK != which_message_)
      {
        init_message(FieldNumber::ACK);
      }
      message_.ack_ = value;
    }
    inline void set_ack(const AckNack&& value)
    {
      if(FieldNumber::ACK != which_message_)
      {
        init_message(FieldNumber::ACK);
      }
      message_.ack_ = value;
    }
    inline AckNack& mutable_ack()
    {
      if(FieldNumber::ACK != which_message_)
      {
        init_message(FieldNumber::ACK);
      }
      return message_.ack_;
    }
    inline const AckNack& get_ack() const { return message_.ack_; }
    inline const AckNack& ack() const { return message_.ack_; }

    static constexpr char const* NACK_NAME = "nack";
    inline bool has_nack() const
    {
      return FieldNumber::NACK == which_message_;
    }
    inline void clear_nack()
    {
      if(FieldNumber::NACK == which_message_)
      {
        which_message_ = FieldNumber::NOT_SET;
        message_.nack_.~AckNack();
      }
    }
    inline void set_nack(const AckNack& value)
    {
      if(FieldNumber::NACK != which_message_)
      {
        init_message(FieldNumber::NACK);
      }
      message_.nack_ = value;
    }
    inline void set_nack(const AckNack&& value)
    {
      if(FieldNumber::NACK != which_message_)
      {
        init_message(FieldNumber::NACK);
      }
      message_.nack_ = value;
    }
    inline AckNack& mutable_nack()
    {
      if(FieldNumber::NACK != which_message_)
      {
        init_message(FieldNumber::NACK);
      }
      return message_.nack_;
    }
    inline const AckNack& get_nack() const { return message_.nack_; }
    inline const AckNack& nack() const { return message_.nack_; }

    static constexpr char const* PING_NAME = "ping";
    inline bool has_ping() const
    {
      return FieldNumber::PING == which_message_;
    }
    inline void clear_ping()
    {
      if(FieldNumber::PING == which_message_)
      {
        which_message_ = FieldNumber::NOT_SET;
        message_.ping_.~Ping();
      }
    }
    inline void set_ping(const Ping& value)
    {
      if(FieldNumber::PING != which_message_)
      {
        init_message(FieldNumber::PING);
      }
      message_.ping_ = value;
    }
    inline void set_ping(const Ping&& value)
    {
      if(FieldNumber::PING != which_message_)
      {
        init_message(FieldNumber::PING);
      }
      message_.ping_ = value;
    }
    inline Ping& mutable_ping()
    {
      if(FieldNumber::PING != which_message_)
      {
        init_message(FieldNumber::PING);
      }
      return message_.ping_;
    }
    inline const Ping& get_ping() const { return message_.ping_; }
    inline const Ping& ping() const { return message_.ping_; }

    static constexpr char const* HB_NAME = "hb";
    inline bool has_hb() const
    {
      return FieldNumber::HB == which_message_;
    }
    inline void clear_hb()
    {
      if(FieldNumber::HB == which_message_)
      {
        which_message_ = FieldNumber::NOT_SET;
        message_.hb_.~Heartbeat();
      }
    }
    inline void set_hb(const Heartbeat& value)
    {
      if(FieldNumber::HB != which_message_)
      {
        init_message(FieldNumber::HB);
      }
      message_.hb_ = value;
    }
    inline void set_hb(const Heartbeat&& value)
    {
      if(FieldNumber::HB != which_message_)
      {
        init_message(FieldNumber::HB);
      }
      message_.hb_ = value;
    }
    inline Heartbeat& mutable_hb()
    {
      if(FieldNumber::HB != which_message_)
      {
        init_message(FieldNumber::HB);
      }
      return message_.hb_;
    }
    inline const Heartbeat& get_hb() const { return message_.hb_; }
    inline const Heartbeat& hb() const { return message_.hb_; }

    static constexpr char const* SYS_STATE_NAME = "sys_state";
    inline bool has_sys_state() const
    {
      return FieldNumber::SYS_STATE == which_message_;
    }
    inline void clear_sys_state()
    {
      if(FieldNumber::SYS_STATE == which_message_)
      {
        which_message_ = FieldNumber::NOT_SET;
        message_.sys_state_.~SystemState();
      }
    }
    inline void set_sys_state(const SystemState& value)
    {
      if(FieldNumber::SYS_STATE != which_message_)
      {
        init_message(FieldNumber::SYS_STATE);
      }
      message_.sys_state_ = value;
    }
    inline void set_sys_state(const SystemState&& value)
    {
      if(FieldNumber::SYS_STATE != which_message_)
      {
        init_message(FieldNumber::SYS_STATE);
      }
      message_.sys_state_ = value;
    }
    inline SystemState& mutable_sys_state()
    {
      if(FieldNumber::SYS_STATE != which_message_)
      {
        init_message(FieldNumber::SYS_STATE);
      }
      return message_.sys_state_;
    }
    inline const SystemState& get_sys_state() const { return message_.sys_state_; }
    inline const SystemState& sys_state() const { return message_.sys_state_; }

    static constexpr char const* SYS_CTRL_NAME = "sys_ctrl";
    inline bool has_sys_ctrl() const
    {
      return FieldNumber::SYS_CTRL == which_message_;
    }
    inline void clear_sys_ctrl()
    {
      if(FieldNumber::SYS_CTRL == which_message_)
      {
        which_message_ = FieldNumber::NOT_SET;
        message_.sys_ctrl_.~SystemControl();
      }
    }
    inline void set_sys_ctrl(const SystemControl& value)
    {
      if(FieldNumber::SYS_CTRL != which_message_)
      {
        init_message(FieldNumber::SYS_CTRL);
      }
      message_.sys_ctrl_ = value;
    }
    inline void set_sys_ctrl(const SystemControl&& value)
    {
      if(FieldNumber::SYS_CTRL != which_message_)
      {
        init_message(FieldNumber::SYS_CTRL);
      }
      message_.sys_ctrl_ = value;
    }
    inline SystemControl& mutable_sys_ctrl()
    {
      if(FieldNumber::SYS_CTRL != which_message_)
      {
        init_message(FieldNumber::SYS_CTRL);
      }
      return message_.sys_ctrl_;
    }
    inline const SystemControl& get_sys_ctrl() const { return message_.sys_ctrl_; }
    inline const SystemControl& sys_ctrl() const { return message_.sys_ctrl_; }


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

      if((static_cast<MessageID>(0) != message_id_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = message_id_.serialize_with_id(static_cast<uint32_t>(FieldNumber::MESSAGE_ID), buffer, false);
      }

      if((0U != source_sequence_num_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = source_sequence_num_.serialize_with_id(static_cast<uint32_t>(FieldNumber::SOURCE_SEQUENCE_NUM), buffer, false);
      }

      switch(which_message_)
      {
        case FieldNumber::ACK:
          if(has_ack() && (::EmbeddedProto::Error::NO_ERRORS == return_value))
          {
            return_value = message_.ack_.serialize_with_id(static_cast<uint32_t>(FieldNumber::ACK), buffer, true);
          }
          break;

        case FieldNumber::NACK:
          if(has_nack() && (::EmbeddedProto::Error::NO_ERRORS == return_value))
          {
            return_value = message_.nack_.serialize_with_id(static_cast<uint32_t>(FieldNumber::NACK), buffer, true);
          }
          break;

        case FieldNumber::PING:
          if(has_ping() && (::EmbeddedProto::Error::NO_ERRORS == return_value))
          {
            return_value = message_.ping_.serialize_with_id(static_cast<uint32_t>(FieldNumber::PING), buffer, true);
          }
          break;

        case FieldNumber::HB:
          if(has_hb() && (::EmbeddedProto::Error::NO_ERRORS == return_value))
          {
            return_value = message_.hb_.serialize_with_id(static_cast<uint32_t>(FieldNumber::HB), buffer, true);
          }
          break;

        case FieldNumber::SYS_STATE:
          if(has_sys_state() && (::EmbeddedProto::Error::NO_ERRORS == return_value))
          {
            return_value = message_.sys_state_.serialize_with_id(static_cast<uint32_t>(FieldNumber::SYS_STATE), buffer, true);
          }
          break;

        case FieldNumber::SYS_CTRL:
          if(has_sys_ctrl() && (::EmbeddedProto::Error::NO_ERRORS == return_value))
          {
            return_value = message_.sys_ctrl_.serialize_with_id(static_cast<uint32_t>(FieldNumber::SYS_CTRL), buffer, true);
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

          case FieldNumber::SOURCE_SEQUENCE_NUM:
            return_value = source_sequence_num_.deserialize_check_type(buffer, wire_type);
            break;

          case FieldNumber::ACK:
          case FieldNumber::NACK:
          case FieldNumber::PING:
          case FieldNumber::HB:
          case FieldNumber::SYS_STATE:
          case FieldNumber::SYS_CTRL:
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
      clear_source_sequence_num();
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
        case FieldNumber::SOURCE_SEQUENCE_NUM:
          name = SOURCE_SEQUENCE_NUM_NAME;
          break;
        case FieldNumber::ACK:
          name = ACK_NAME;
          break;
        case FieldNumber::NACK:
          name = NACK_NAME;
          break;
        case FieldNumber::PING:
          name = PING_NAME;
          break;
        case FieldNumber::HB:
          name = HB_NAME;
          break;
        case FieldNumber::SYS_STATE:
          name = SYS_STATE_NAME;
          break;
        case FieldNumber::SYS_CTRL:
          name = SYS_CTRL_NAME;
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
      left_chars = source_sequence_num_.to_string(left_chars, indent_level + 2, SOURCE_SEQUENCE_NUM_NAME, false);
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
      EmbeddedProto::enumeration<MessageID> message_id_ = static_cast<MessageID>(0);
      EmbeddedProto::uint32 source_sequence_num_ = 0U;

      FieldNumber which_message_ = FieldNumber::NOT_SET;
      union message
      {
        message() {}
        ~message() {}
        AckNack ack_;
        AckNack nack_;
        Ping ping_;
        Heartbeat hb_;
        SystemState sys_state_;
        SystemControl sys_ctrl_;
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
          case FieldNumber::ACK:
            new(&message_.ack_) AckNack;
            break;

          case FieldNumber::NACK:
            new(&message_.nack_) AckNack;
            break;

          case FieldNumber::PING:
            new(&message_.ping_) Ping;
            break;

          case FieldNumber::HB:
            new(&message_.hb_) Heartbeat;
            break;

          case FieldNumber::SYS_STATE:
            new(&message_.sys_state_) SystemState;
            break;

          case FieldNumber::SYS_CTRL:
            new(&message_.sys_ctrl_) SystemControl;
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
          case FieldNumber::ACK:
            ::EmbeddedProto::destroy_at(&message_.ack_);
            break;
          case FieldNumber::NACK:
            ::EmbeddedProto::destroy_at(&message_.nack_);
            break;
          case FieldNumber::PING:
            ::EmbeddedProto::destroy_at(&message_.ping_);
            break;
          case FieldNumber::HB:
            ::EmbeddedProto::destroy_at(&message_.hb_);
            break;
          case FieldNumber::SYS_STATE:
            ::EmbeddedProto::destroy_at(&message_.sys_state_);
            break;
          case FieldNumber::SYS_CTRL:
            ::EmbeddedProto::destroy_at(&message_.sys_ctrl_);
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
          case FieldNumber::ACK:
            return_value = message_.ack_.deserialize_check_type(buffer, wire_type);
            break;
          case FieldNumber::NACK:
            return_value = message_.nack_.deserialize_check_type(buffer, wire_type);
            break;
          case FieldNumber::PING:
            return_value = message_.ping_.deserialize_check_type(buffer, wire_type);
            break;
          case FieldNumber::HB:
            return_value = message_.hb_.deserialize_check_type(buffer, wire_type);
            break;
          case FieldNumber::SYS_STATE:
            return_value = message_.sys_state_.deserialize_check_type(buffer, wire_type);
            break;
          case FieldNumber::SYS_CTRL:
            return_value = message_.sys_ctrl_.deserialize_check_type(buffer, wire_type);
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
          case FieldNumber::ACK:
            left_chars = message_.ack_.to_string(left_chars, indent_level, ACK_NAME, first_field);
            break;
          case FieldNumber::NACK:
            left_chars = message_.nack_.to_string(left_chars, indent_level, NACK_NAME, first_field);
            break;
          case FieldNumber::PING:
            left_chars = message_.ping_.to_string(left_chars, indent_level, PING_NAME, first_field);
            break;
          case FieldNumber::HB:
            left_chars = message_.hb_.to_string(left_chars, indent_level, HB_NAME, first_field);
            break;
          case FieldNumber::SYS_STATE:
            left_chars = message_.sys_state_.to_string(left_chars, indent_level, SYS_STATE_NAME, first_field);
            break;
          case FieldNumber::SYS_CTRL:
            left_chars = message_.sys_ctrl_.to_string(left_chars, indent_level, SYS_CTRL_NAME, first_field);
            break;
          default:
            break;
        }

        return left_chars;
      }

#endif // End of MSG_TO_STRING
};

} // End of namespace Proto
#endif // CONTROLMESSAGE_H