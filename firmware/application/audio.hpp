/*
 * Copyright (C) 2014 Jared Boone, ShareBrained Technology, Inc.
 *
 * This file is part of PortaPack.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#ifndef __AUDIO_H__
#define __AUDIO_H__

#include "volume.hpp"

#include <cstdint>
#include <cstddef>

#include <string>

namespace audio {

class Codec {
public:
	virtual ~Codec() { }

	virtual std::string name() const = 0;

	virtual bool reset() = 0;
	virtual void init() = 0;

	virtual void headphone_enable() = 0;
	virtual void headphone_disable() = 0;
	virtual volume_range_t headphone_gain_range() const = 0;
	virtual void set_headphone_volume(const volume_t volume) = 0;

	virtual void microphone_enable() = 0;
	virtual void microphone_disable() = 0;

	virtual size_t reg_count() const = 0;
	virtual size_t reg_bits() const = 0;
	virtual uint32_t reg_read(const size_t register_number) = 0;
};

namespace output {

void start();
void stop();

void mute();
void unmute();

} /* namespace output */

namespace input {

void start();
void stop();

} /* namespace input */

namespace headphone {

volume_range_t volume_range();

void set_volume(const volume_t volume);

} /* namespace headphone */

namespace debug {

size_t reg_count();
uint32_t reg_read(const size_t register_number);
std::string codec_name();
size_t reg_bits();

} /* namespace debug */

void init(audio::Codec* const codec);
void shutdown();

enum class Rate {
	Hz_12000 = 4,
	Hz_24000 = 2,
	Hz_48000 = 1,
};

void set_rate(const Rate rate);

} /* namespace audio */

#endif/*__AUDIO_H__*/
