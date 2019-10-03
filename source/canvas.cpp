/*
 * This file is part of Fractol.

 * Fractol is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Fractol is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Fractol. If not, see <https://www.gnu.org/licenses/>.
 *
 * Author: Pavlo Hrytsenko
*/

#include "canvas.hpp"

namespace cozz {

Canvas::PixelFormat::PixelFormat()
    : bits_per_pixel(kMinBitsPerPixel),
      bytes_per_pixel(kMinBytesPerPixel),
      r_mask(0x30),
      g_mask(0x0C),
      b_mask(0x03),
      a_mask(0xC0),
      r_loss(0x0),
      g_loss(0x0),
      b_loss(0x0),
      a_loss(0x0),
      r_shift(0x4),
      g_shift(0x2),
      b_shift(0x0),
      a_shift(0x6) {}

Canvas::PixelFormat::PixelFormat(uint8_t bits_per_pixel, uint8_t bytes_per_pixel, uint32_t r_mask, uint32_t g_mask,
                                 uint32_t b_mask, uint32_t a_mask, uint8_t r_loss, uint8_t g_loss, uint8_t b_loss,
                                 uint8_t a_loss, uint8_t r_shift, uint8_t g_shift, uint8_t b_shift, uint8_t a_shift)
    : bits_per_pixel(std::clamp(bits_per_pixel, kMinBitsPerPixel, kMaxBitsPerPixel)),
      bytes_per_pixel(std::clamp(bytes_per_pixel, kMinBytesPerPixel, kMaxBytesPerPixel)),
      r_mask(r_mask),
      g_mask(g_mask),
      b_mask(b_mask),
      a_mask(a_mask),
      r_loss(r_loss),
      g_loss(g_loss),
      b_loss(b_loss),
      a_loss(a_loss),
      r_shift(r_shift),
      g_shift(g_shift),
      b_shift(b_shift),
      a_shift(a_shift) {}

Canvas::iterator::iterator(uint8_t* pos, const PixelFormat& pixel_format) : pos_(pos), pixel_format_(pixel_format) {}

bool Canvas::iterator::operator==(const Canvas::iterator& other) const { return pos_ == other.pos_; }

bool Canvas::iterator::operator!=(const Canvas::iterator& other) const { return pos_ != other.pos_; }

Canvas::iterator& Canvas::iterator::operator=(uint32_t value) {
    std::copy_n(reinterpret_cast<uint8_t*>(&value), sizeof(value), pos_);
    return *this;
}

Canvas::iterator& Canvas::iterator::operator*() { return *this; }

Canvas::iterator::operator uint32_t() const {
    uint32_t ret = 0;

    std::copy_n(pos_, pixel_format_.bytes_per_pixel, reinterpret_cast<uint8_t*>(&ret));
    return ret;
}

Canvas::iterator Canvas::iterator::operator++() { pos_ += pixel_format_.bytes_per_pixel; }

uint8_t Canvas::iterator::R() const {
    uint32_t pixel = *this;
    return static_cast<uint8_t>(((pixel & pixel_format_.r_mask) >> pixel_format_.r_shift) << pixel_format_.r_loss);
}

void Canvas::iterator::R(uint8_t channel) {
    uint32_t pixel = *this;
    *this = (pixel & (~pixel_format_.r_mask)) | (channel << pixel_format_.r_shift);
}

uint8_t Canvas::iterator::G() const {
    uint32_t pixel = *this;
    return static_cast<uint8_t>(((pixel & pixel_format_.g_mask) >> pixel_format_.g_shift) << pixel_format_.g_loss);
}

void Canvas::iterator::G(uint8_t channel) {
    uint32_t pixel = *this;
    *this = (pixel & (~pixel_format_.g_mask)) | (channel << pixel_format_.g_shift);
}

uint8_t Canvas::iterator::B() const {
    uint32_t pixel = *this;
    return static_cast<uint8_t>(((pixel & pixel_format_.b_mask) >> pixel_format_.b_shift) << pixel_format_.b_loss);
}

void Canvas::iterator::B(uint8_t channel) {
    uint32_t pixel = *this;
    *this = (pixel & (~pixel_format_.b_mask)) | (channel << pixel_format_.b_shift);
}

uint8_t Canvas::iterator::A() const {
    uint32_t pixel = *this;
    return static_cast<uint8_t>(((pixel & pixel_format_.a_mask) >> pixel_format_.a_shift) << pixel_format_.a_loss);
}

void Canvas::iterator::A(uint8_t channel) {
    uint32_t pixel = *this;
    *this = (pixel & (~pixel_format_.a_mask)) | (channel << pixel_format_.a_shift);
}

Canvas::Canvas(uint64_t width, uint64_t height, const PixelFormat& pixel_format)
    : Canvas(width, height, new uint8_t[width * height * pixel_format.bytes_per_pixel], pixel_format,
             std::default_delete<uint8_t[]>()) {}

Canvas::Canvas(uint64_t width, uint64_t height, uint8_t* pixels, const PixelFormat& pixel_format,
               std::function<void(uint8_t*)> deleter)
    : width_(width),
      height_(height),
      pixel_format_(pixel_format),
      pitch_(width_ * pixel_format_.bytes_per_pixel),
      pixels_(std::shared_ptr<uint8_t[]>(pixels, deleter)) {}

uint64_t Canvas::GetWidth() const { return width_; }

uint64_t Canvas::GetHeight() const { return height_; }

uint64_t Canvas::GetPitch() const { return pitch_; }

const Canvas::PixelFormat& Canvas::GetPixelFormat() const { return pixel_format_; }

Canvas::iterator Canvas::begin() { return iterator(pixels_.get(), pixel_format_); }

Canvas::const_iterator Canvas::cbegin() const { return const_iterator(pixels_.get(), pixel_format_); }

Canvas::iterator Canvas::end() { return iterator(&pixels_[height_ * pitch_], pixel_format_); }

Canvas::const_iterator Canvas::cend() const { return const_iterator(&pixels_[height_ * pitch_], pixel_format_); }

Canvas::iterator Canvas::At(uint64_t x, uint64_t y) {
    return iterator(GetRawPixels() + y * pitch_ + x * pixel_format_.bytes_per_pixel, pixel_format_);
}

uint8_t* Canvas::GetRawPixels() const { return pixels_.get(); }

}  // namespace cozz