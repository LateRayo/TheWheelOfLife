#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cairo/cairo.h>
#include <math.h>

#define MAX_FIELDS 12
#define MAX_NAME_LENGTH 50
#define IMAGE_WIDTH 800
#define IMAGE_HEIGHT 800

typedef struct {
    char name[MAX_NAME_LENGTH];
    int level; // Level for the field, ranging from 1 to 10
    double color[3]; // RGB color values, each ranging from 0 to 1
} LifeField;

// Function to draw the "Wheel of Life" diagram and save it as a PNG file
void draw_wheel(LifeField *fields, int field_count, const char *filename) 
{
    // Create a new image surface and a Cairo context for drawing
    cairo_surface_t *surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, IMAGE_WIDTH, IMAGE_HEIGHT);
    cairo_t *cr = cairo_create(surface);

    // Define the center and radius of the wheel
    double center_x = IMAGE_WIDTH / 2.0;
    double center_y = IMAGE_HEIGHT / 2.0;
    double radius = (IMAGE_WIDTH < IMAGE_HEIGHT ? IMAGE_WIDTH : IMAGE_HEIGHT) / 2.5;
    double angle_step = 2 * M_PI / field_count; // Calculate the angle step for each field

    // Set the background color (white)
    cairo_set_source_rgb(cr, 1.0, 1.0, 1.0);
    cairo_rectangle(cr, 0, 0, IMAGE_WIDTH, IMAGE_HEIGHT);
    cairo_fill(cr);

    // Draw concentric circles to represent the levels (1 to 10)
    cairo_set_line_width(cr, 1);
    cairo_set_source_rgb(cr, 0.8, 0.8, 0.8); // Light gray for level lines
    for (int i = 1; i <= 10; i++) 
    {
        cairo_arc(cr, center_x, center_y, radius * i / 10, 0, 2 * M_PI);
        cairo_stroke(cr);
    }

    // Draw each field of the wheel
    for (int i = 0; i < field_count; i++) 
    {
        double start_angle = i * angle_step; // Start angle for the field
        double end_angle = (i + 1) * angle_step; // End angle for the field
        double field_radius = radius * fields[i].level / 10; // Radius proportional to the level

        // Validate and clamp color values to ensure they are within the [0, 1] range
        for (int j = 0; j < 3; j++) {
            if (fields[i].color[j] < 0.0) fields[i].color[j] = 0.0;
            if (fields[i].color[j] > 1.0) fields[i].color[j] = 1.0;
        }

        // Set the color for the current field
        cairo_set_source_rgb(cr, fields[i].color[0], fields[i].color[1], fields[i].color[2]);

        // Draw and fill the section representing the field
        cairo_move_to(cr, center_x, center_y);
        cairo_arc(cr, center_x, center_y, field_radius, start_angle, end_angle);
        cairo_close_path(cr);
        cairo_fill(cr);

        // Draw the border of the section
        cairo_set_source_rgb(cr, 0, 0, 0); // Black for the border
        cairo_move_to(cr, center_x, center_y);
        cairo_arc(cr, center_x, center_y, radius, start_angle, end_angle);
        cairo_close_path(cr);
        cairo_stroke(cr);

        // Add the name of the field
        double text_angle = (start_angle + end_angle) / 2; // Angle for the text
        double text_x = center_x + (radius + 20) * cos(text_angle); // Text position (x)
        double text_y = center_y + (radius + 20) * sin(text_angle); // Text position (y)

        cairo_set_source_rgb(cr, 0, 0, 0); // Black text
        cairo_set_font_size(cr, 14);
        cairo_move_to(cr, text_x, text_y);
        cairo_save(cr); // Save the current transformation matrix
        cairo_rotate(cr, text_angle); // Rotate the context for angled text
        cairo_show_text(cr, fields[i].name); // Draw the text
        cairo_restore(cr); // Restore the original transformation matrix
    }

    // Save the drawing to a PNG file
    cairo_surface_write_to_png(surface, filename);

    // Clean up resources
    cairo_destroy(cr);
    cairo_surface_destroy(surface);
}

int main() {
    int field_count; // Number of fields in the wheel
    LifeField fields[MAX_FIELDS]; // Array to store field data

    // Prompt the user to enter the number of life fields
    printf("Enter the number of life fields (max %d): ", MAX_FIELDS);
    scanf("%d", &field_count);

    // Validate the number of fields
    if (field_count < 1 || field_count > MAX_FIELDS) {
        printf("Invalid number of fields. Exiting.\n");
        return 1;
    }

    // Loop to get data for each field
    for (int i = 0; i < field_count; i++) {
        printf("Enter the name of field %d: ", i + 1);
        scanf("%s", fields[i].name);

        printf("Enter the level for %s (1-10): ", fields[i].name);
        scanf("%d", &fields[i].level);

        // Validate the level input
        if (fields[i].level < 1 || fields[i].level > 10) {
            printf("Invalid level. Exiting.\n");
            return 1;
        }

        printf("Enter the RGB color for %s (0-1 each, space-separated): ", fields[i].name);
        scanf("%lf %lf %lf", &fields[i].color[0], &fields[i].color[1], &fields[i].color[2]);
    }

    // Draw the wheel of life and save it to a file
    draw_wheel(fields, field_count, "wheel_of_life.png");
    printf("Wheel of life saved as 'wheel_of_life.png'.\n");

    return 0;
}
