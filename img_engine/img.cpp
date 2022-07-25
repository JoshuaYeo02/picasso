#include "img.h"
using namespace std;

Img::Img() {
	width = 0;
	height = 0;
}
Img::Img(int w, int h) {
    width = w;
    height = h;
    pixels.resize(height, vector<Pixel>(width, Pixel(255, 255, 255)));
}

Img::Img(string const file) {
    readFromFile(file);
}

Img::Img(Img const& o) {
    width = o.width;
    height = o.height;
    pixels.resize(height, vector<Pixel>(width));
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            pixels[y][x] = o.pixels[y][x];
        }
    }
}

Img::~Img() {
    for (auto t : pixels) {
        t.clear();
    }
    pixels.clear();
}

Pixel Img::operator()(int x, int y) {
    return pixels[y][x];
}

bool Img::readFromFile(string const file) {
    FILE* fp = fopen(file.c_str(), "rb");
    if (!fp) {
        cerr << "Failed to open " << file << endl;
        return false;
    }

    png_byte header[8];
    fread(header, 1, 8, fp);
    if (png_sig_cmp(header, 0, 8)) {
        cout << "File is not a valid PNG file" << endl;
        fclose(fp);
        return false;
    }

    png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!png_ptr) {
        cerr << "Failed to create read struct" << endl;
        fclose(fp);
        return false;
    }

    png_infop info_ptr = png_create_info_struct(png_ptr);
    if (!info_ptr) {
        cerr << "Failed to create info struct" << endl;
        png_destroy_read_struct(&png_ptr, NULL, NULL);
        fclose(fp);
        return false;
    }

    if (setjmp(png_jmpbuf(png_ptr))) {
        cerr << "Error initializing libpng io" << endl;
		png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
		fclose(fp);
		return false;
	}

    png_init_io(png_ptr, fp);

    png_set_sig_bytes(png_ptr, 8);

    png_read_info(png_ptr, info_ptr);

    png_byte bit_depth = png_get_bit_depth(png_ptr, info_ptr);
    if (bit_depth == 16) {
        png_set_strip_16(png_ptr);
    }

    png_byte color_type = png_get_color_type(png_ptr, info_ptr);
	if (color_type != PNG_COLOR_TYPE_RGBA && color_type != PNG_COLOR_TYPE_RGB)
	{
		if (color_type == PNG_COLOR_TYPE_GRAY || color_type == PNG_COLOR_TYPE_GRAY_ALPHA) {
			if (bit_depth < 8)
				png_set_expand(png_ptr);
			png_set_gray_to_rgb(png_ptr);
		}
		if (color_type == PNG_COLOR_TYPE_PALETTE)
			png_set_palette_to_rgb(png_ptr);
	}

    if (png_get_valid(png_ptr, info_ptr, PNG_INFO_tRNS)) {
		png_set_tRNS_to_alpha(png_ptr);
    }

	width = png_get_image_width(png_ptr, info_ptr);
	height = png_get_image_height(png_ptr, info_ptr);

	png_read_update_info(png_ptr, info_ptr);

	if (setjmp(png_jmpbuf(png_ptr))) {
        cerr << "Error reading image with Libpng" << endl;
		png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
		fclose(fp);
		return false;
	}

	int bpr = png_get_rowbytes(png_ptr, info_ptr);
	int numchannels = png_get_channels(png_ptr, info_ptr);    

    pixels.resize(height, vector<Pixel>(width, Pixel()));

	png_byte * row = new png_byte[bpr];

	for (int y = 0; y < height; y++) {
		png_read_row(png_ptr, row, NULL);
		png_byte * pix = row;
		for (int x = 0; x < width; x++) {
			if (numchannels == 1 || numchannels == 2) {
				// monochrome
				unsigned char color = (unsigned char) *pix++;
				pixels[y][x].r = color;
				pixels[y][x].g = color;
				pixels[y][x].b = color;
				if (numchannels == 2)
					pixels[y][x].a = (unsigned char) *pix++;
				else
					pixels[y][x].a = 255;
			} 
			else if (numchannels == 3 || numchannels == 4) {
				pixels[y][x].r = (unsigned char) *pix++;
				pixels[y][x].g = (unsigned char) *pix++;
				pixels[y][x].b = (unsigned char) *pix++;
				if (numchannels == 4)
					pixels[y][x].a = (unsigned char) *pix++;
				else
					pixels[y][x].a = 255;
			}
		}
	}
	// cleanup
	delete [] row;
	png_read_end(png_ptr, NULL);
	png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
	fclose(fp);
	return true;
}

bool Img::writeToFile (string const file) {
	FILE * fp = fopen(file.c_str(), "wb");
	if (!fp) {
		cerr << "Failed to open " << file << endl;
		return false;
	}

	png_structp png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	if (!png_ptr) {
        cerr << "Failed to create png struct" << endl;
		fclose(fp);
		return false;
	}

	png_infop info_ptr = png_create_info_struct(png_ptr);
	if (!info_ptr) {
        cerr << "Failed to create png info struct" << endl;
		png_destroy_write_struct(&png_ptr, NULL);
		fclose(fp);
		return false;
	}

	if (setjmp(png_jmpbuf(png_ptr))) {
        cerr << "Error initializing libpng io" << endl;
		png_destroy_write_struct(&png_ptr, &info_ptr);
		fclose(fp);
		return false;
	}

	png_init_io(png_ptr, fp);

	// write header
	if (setjmp(png_jmpbuf(png_ptr))) {
        cerr << "Error writing image header" << endl;
		png_destroy_write_struct(&png_ptr, &info_ptr);
		fclose(fp);
		return false;
	}

	png_set_IHDR(png_ptr, info_ptr, width, height, 
			8,
			PNG_COLOR_TYPE_RGB_ALPHA, 
			PNG_INTERLACE_NONE, 
			PNG_COMPRESSION_TYPE_BASE,
			PNG_FILTER_TYPE_BASE);

	png_write_info(png_ptr, info_ptr);

	// write image
	if (setjmp(png_jmpbuf(png_ptr)))
	{
        cout << "Failed to write image" << endl;
		png_destroy_write_struct(&png_ptr, &info_ptr);
		fclose(fp);
		return false;
	}

	int bpr = png_get_rowbytes(png_ptr, info_ptr);
	png_byte * row = new png_byte[bpr];
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			png_byte * pix = &(row[x*4]);
			pix[0] = pixels[y][x].r;
			pix[1] = pixels[y][x].g;
			pix[2] = pixels[y][x].b;
			pix[3] = pixels[y][x].a;
		}
		png_write_row(png_ptr, row);
	}
	delete [] row;
	png_write_end(png_ptr, NULL);
	png_destroy_write_struct(&png_ptr, &info_ptr);
	fclose(fp);
	return true;
}

int Img::getWidth() {
    return width;
}

int Img::getHeight() {
    return height;
}

vector<pair<int, int>> Img::circleRange(int cx, int cy, int r) {
	int top = cy - r;
	int bottom = cy + r;
	int left = cx - r;
	int right = cx + r;
	vector<pair<int, int>> range;
	if (top < 0) {
		top = 0;
	}
	if (bottom >= getHeight()) {
		bottom = getHeight();
	}
	if (left < 0) {
		left = 0;
	}
	if (right >= getWidth()) {
		right = getWidth();
	}
	for (int y = top; y < bottom; y++) {
		for (int x = left; x < right; x++) {
			if (pow(y - cy, 2) + pow(x - cx, 2) < pow(r, 2)) {
				range.push_back(make_pair(x, y));
			}
		}
	}
	return range;
}

bool Img::drawCircle(int x, int y, int r, int red, int green, int blue) {
	vector<pair<int, int>> range = circleRange(x, y, r);
	for (pair<int, int> p : range) {
		pixels[p.second][p.first].r = red;
		pixels[p.second][p.first].g = green;
		pixels[p.second][p.first].b = blue;
	}
	return true;
}