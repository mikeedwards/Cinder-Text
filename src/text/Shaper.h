#pragma once

#include <memory>
#include <string>

#include "harfbuzz/hb.h"
#include "cinder/Vector.h"
#include "text/Font.h"

namespace txt
{
	class Shaper
	{
		public:
			enum Feature {
				LIGATURES,
				KERNING,
				CLIG
			};

			typedef struct {
				std::string data;
				std::string language;
				hb_script_t script;
				hb_direction_t direction;
				const char* c_data() { return data.c_str(); };
			} Text;

			typedef struct {
				uint32_t index;

				ci::vec2 pos;
				ci::vec2 offset;
				ci::vec2 advance;
			} Glyph;

			Shaper( Font& font );
			~Shaper();

			std::vector<Glyph> getShapedText( Text& text );
			void addFeature( Feature feature );
			void removeFeature( Feature feature );

		private:
			// Harfbuzz
			hb_font_t* getHarfbuzzFont( Font& font );

			hb_font_t* mFont;
			hb_buffer_t* mBuffer;
			std::vector<hb_feature_t> mFeatures;
	};
}