#include "libMPEG2Stream.h"

#pragma once

#ifndef LIBMPEG2STREAM_MPEG2STREAMTYPES_H
#define LIBMPEG2STREAM_MPEG2STREAMTYPES_H

#ifdef __cplusplus
extern "C" {
#endif
    
    typedef struct ProgramStreamPacket { // Can be the most basic level as well as the TransportStream
        uint64_t  SystemClockRefBase:33;                // system_clock_reference_base
        uint32_t  ProgramMuxRate:22;                    // program_mux_rate
        uint16_t  SystemClockRefBase2:15;               // system_clock_reference_base [29..15]
        uint16_t  SystemClockRefBase3:15;               // system_clock_reference_base [14..0]
        uint16_t  SystemClockRefExtension:9;            // system_clock_reference_extension
        uint8_t   PackStartCode;                        // pack_start_code
        uint8_t   SystemClockRefBase1:3;                // system_clock_reference_base [32..30]
        uint8_t   PackStuffingSize:3;                   // pack_stuffing_length
    } ProgramStreamPacket;
    
    typedef struct TransportStreamPacket {
        uint16_t  PID:13;                              // PID
        int8_t    SyncByte;                            // sync_byte
        uint8_t   ContinuityCounter:4;                 // continuity_counter
        int8_t    TransportScramblingControl:2;        // transport_scrambling_control
        int8_t    AdaptationFieldControl:2;            // adaptation_field_control
        bool      TransportErrorIndicator:1;           // transport_error_indicator
        bool      StartOfPayloadIndicator:1;           // payload_unit_start_indicator
        bool      TransportPriorityIndicator:1;        // transport_priority
    } TransportStreamPacket;
    
    typedef struct PacketizedElementaryStream { // This is contains the actual video and audio streams, it differs from them by offering a very thin layer on top to split the NALs and SliceGroups into packets.
        uint64_t  PTS:33;                              // PTS
        uint64_t  DTS:33;                              // DTS
        uint64_t  ESCR:33;                             // ESCR
        uint64_t  TREF:33;                             // TREF
        int32_t   PacketStartCodePrefix:24;            // packet_start_code_prefix
        uint32_t  ESRate:22;                           // ES_rate
        uint16_t  PESPacketSize;                       // PES_packet_length
        uint16_t  PreviousPESPacketCRC;                // previous_PES_packet_CRC
        uint16_t  PSTDBufferSize:13;                   // P-STD_buffer_size
        uint8_t   StreamID;                            // stream_id
        uint8_t   PESScramblingControl;                // PES_scrambling_control
        uint8_t   PESHeaderSize;                       // PES_header_data_length
        uint8_t   PackFieldSize;                       // pack_field_length
        uint8_t   AdditionalCopyInfo:7;                // additional_copy_info
        uint8_t   ProgramPacketSeqCounter:7;           // program_packet_sequence_counter
        uint8_t   PESExtensionFieldSize:7;             // PES_extension_field_length
        uint8_t   StreamIDExtension:7;                 // stream_id_extension
        uint8_t   OriginalStuffSize:6;                 // original_stuff_length
        uint8_t   RepetitionControl:5;                 // rep_cntrl
        uint8_t   TrickModeControl:3;                  // trick_mode_control
        uint8_t   PTSDTSFlags:2;                       // PTS_DTS_flags
        uint8_t   FieldID:2;                           // field_id
        uint8_t   FrequencyTruncation:2;               // frequency_truncation
        uint8_t   PSTDBufferScale:1;                   // P-STD_buffer_scale
        bool      PESPriority:1;                       // PES_priority
        bool      AlignmentIndicator:1;                // data_alignment_indicator
        bool      CopyrightIndicator:1;                // copyright
        bool      OriginalOrCopy:1;                    // original_or_copy
        bool      ESCRFlag:1;                          // ESCR_flag
        bool      ESRateFlag:1;                        // ES_rate_flag
        bool      DSMTrickModeFlag:1;                  // DSM_trick_mode_flag
        bool      AdditionalCopyInfoFlag:1;            // additional_copy_info_flag
        bool      PESCRCFlag:1;                        // PES_CRC_flag
        bool      PESExtensionFlag:1;                  // PES_extension_flag
        bool      IntraSliceRefresh:1;                 // intra_slice_refresh
        bool      PESPrivateDataFlag:1;                // PES_private_data_flag
        bool      PackHeaderFieldFlag:1;               // pack_header_field_flag
        bool      ProgramPacketSeqCounterFlag:1;       // program_packet_sequence_counter_flag
        bool      PSTDBufferFlag:1;                    // P-STD_buffer_flag
        bool      PESExtensionFlag2:1;                 // PES_extension_flag_2
        bool      MPEGVersionIdentifier:1;             // MPEG1_MPEG2_identifier
        bool      StreamIDExtensionFlag:1;             // stream_id_extension_flag
        bool      TREFFieldPresentFlag:1;              // tref_extension_flag
    } PacketizedElementaryStream;
    
    typedef struct ConditionalAccessSection {
        uint32_t  ConditionCRC32;                      // CRC_32
        uint16_t  SectionSize:12;                      // section_length
        uint8_t   TableID;                             // table_id
        uint8_t   SectionNumber;                       // section_number
        uint8_t   LastSectionNumber;                   // last_section_number
        uint8_t   VersionNum:5;                        // version_number
        bool      SectionSyntaxIndicator:1;            // section_syntax_indicator
        bool      CurrentNextIndicator:1;              // current_next_indicator
    } ConditionalAccessSection;
    
    typedef struct ProgramAssociatedSection {
        uint32_t  ProgramCRC32;                        // CRC_32
        uint16_t  TransportStreamID;                   // transport_stream_id
        uint16_t  ProgramNumber;                       // program_number
        uint16_t  NetworkPID:13;                       // network_PID
        uint16_t  ProgramMapPID:13;                    // program_map_PID
        uint16_t  SectionSize:12;                      // section_length
        uint8_t   TableID;                             // table_id
        uint8_t   SectionNumber;                       // section_number
        uint8_t   LastSectionNumber;                   // last_section_number
        uint8_t   VersionNum:5;                        // version_number
        bool      SectionSyntaxIndicator:1;            // section_syntax_indicator
        bool      CurrentNextIndicator:1;              // current_next_indicator
    } ProgramAssociatedSection;
    
    typedef struct TSAdaptationField {
        uint8_t  *TransportPrivateData;                // private_data_byte
        uint64_t  DecodeTimeStampNextAU:33;            // DTS_next_AU
        uint64_t  ProgramClockReferenceBase:33;        // program_clock_reference_base
        uint64_t  OriginalProgramClockRefBase:33;      // original_program_clock_reference_base
        uint32_t  PiecewiseRate:22;                    // piecewise_rate
        uint16_t  LegalTimeWindowOffset:15;            // ltw_offset
        uint16_t  ProgramClockReferenceExtension:9;    // program_clock_reference_extension
        uint16_t  OriginalProgramClockRefExt:9;        // original_program_clock_reference_extension
        uint8_t   AdaptationFieldSize;                 // adaptation_field_length
        uint8_t   TransportPrivateDataSize;            // transport_private_data_length
        uint8_t   AdaptationFieldExtensionSize;        // adaptation_field_extension_length
        int8_t    SpliceCountdown;                     // splice_countdown
        uint8_t   SpliceType:4;                        // Splice_type
        bool      LegalTimeWindowFlag:1;               // ltw_flag
        bool      PiecewiseRateFlag:1;                 // piecewise_rate_flag
        bool      SeamlessSpliceFlag:1;                // seamless_splice_flag
        bool      LegalTimeWindowValidFlag:1;          // ltw_valid_flag
        bool      DiscontinuityIndicator:1;            // discontinuity_indicator
        bool      RandomAccessIndicator:1;             // random_access_indicator
        bool      ElementaryStreamPriorityIndicator:1; // elementary_stream_priority_indicator
        bool      PCRFlag:1;                           // PCR_flag
        bool      OPCRFlag:1;                          // OPCR_flag
        bool      SlicingPointFlag:1;                  // splicing_point_flag
        bool      TransportPrivateDataFlag:1;          // transport_private_data_flag
        bool      AdaptationFieldExtensionFlag:1;      // adaptation_field_extension_flag
    } TSAdaptationField;
    
    typedef struct MPEG2TransportStream {
        TransportStreamPacket      *Packet;
        TSAdaptationField          *Adaptation;
        PacketizedElementaryStream *PES;
        ProgramAssociatedSection   *Program;
        ConditionalAccessSection   *Condition;
    } MPEG2TransportStream;
    
    typedef struct MPEG2ProgramStream {
        ProgramStreamPacket        *PSP;
        PacketizedElementaryStream *PES;
    } MPEG2ProgramStream;
    
    typedef struct Packet2Mux {
        uint8_t *PacketData;
        uint64_t DisplayTime;
        uint16_t PacketSize;
        uint8_t  PacketType;
        bool     IsSubstream;
    } Packet2Mux;
    
#ifdef __cplusplus
}
#endif

#endif /* LIBMPEG2STREAM_MPEG2STREAMTYPES_H */
