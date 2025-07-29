#include "drawthewheel.h"


// Función para dibujar la rueda de la vida
void draw_wheel(LifeField fields[], int field_count, const char* filename)
{
    // Dimensiones del canvas
    int width = 640;
    int height = 500;
    double center_x = width / 2.0;
    double center_y = height / 2.0;
    double max_radius = fmin(width, height) * 0.4; // Radio máximo para la rueda

    // Crear la superficie de Cairo y el contexto
    cairo_surface_t *surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, width, height); // superficie
    cairo_t *cr = cairo_create(surface); //contexto

    // Establecer fondo blanco
    cairo_set_source_rgb(cr, 1, 1, 1);
    cairo_paint(cr);

    // Dibujar círculos concéntricos para representar los niveles
    cairo_set_source_rgb(cr, 0.8, 0.8, 0.8); // Gris claro
    cairo_set_line_width(cr, 0.5);

    for (int level = 1; level <= 10; level++)
    {
        double radius = max_radius * level / 10.0;
        cairo_arc(cr, center_x, center_y, radius, 0, 2 * PI);
        cairo_stroke(cr);
    }

    // Dibujar las lineas de cada segmento de la rueda
    double angle_per_field = 2 * PI / field_count;

    // Primero dibujamos las líneas divisorias de los segmentos
    cairo_set_source_rgb(cr, 0, 0, 0);
    cairo_set_line_width(cr, 1.0); // 1px

    for (int i = 0; i < field_count; i++)
    {
        double angle = i * angle_per_field - PI / 2; // Empezar desde arriba (pi/2)
        cairo_move_to(cr, center_x, center_y);
        double end_x = center_x + max_radius * cos(angle);
        double end_y = center_y + max_radius * sin(angle);
        cairo_line_to(cr, end_x, end_y);
        cairo_stroke(cr);
    }

    // Luego dibujamos los segmentos coloreados para cada nivel
    for (int i = 0; i < field_count; i++)
    {
        // Calcular ángulos para este campo
        double start_angle = i * angle_per_field - PI / 2; // Empezar desde arriba (pi/2)
        double end_angle = (i + 1) * angle_per_field - PI / 2;

        // Dibujar el nivel actual como un arco relleno con transparencia
        double level_radius = max_radius * fields[i].level / 10.0;
        cairo_set_source_rgba(cr, fields[i].color[0], fields[i].color[1], fields[i].color[2], fields[i].color[3]);
        cairo_move_to(cr, center_x, center_y);
        cairo_arc(cr, center_x, center_y, level_radius, start_angle, end_angle);
        cairo_close_path(cr);
        cairo_fill_preserve(cr);
        cairo_set_source_rgba(cr, 0, 0, 0, 0.5);
        cairo_set_line_width(cr, 0.5);
        cairo_stroke(cr);

        // Añadir el nombre del campo
        double text_angle = (start_angle + end_angle) / 2;
        double text_radius = max_radius + (max_radius * 0.13) /*50*/;  // Aumentado para alejar más las etiquetas del borde
        double text_x = center_x + text_radius * cos(text_angle);
        double text_y = center_y + text_radius * sin(text_angle);

        cairo_set_source_rgb(cr, 0, 0, 0);
        cairo_set_font_size(cr, 14);

        // Obtener dimensiones del texto
        cairo_text_extents_t extents;
        cairo_text_extents(cr, fields[i].name, &extents);

        // Ajustar posición basado en el ángulo para mejor legibilidad y evitar cortes
        if (text_angle > -PI/4 && text_angle < PI/4) {
            // Texto a la derecha
            cairo_move_to(cr, text_x, text_y + extents.height/2);
        } else if (text_angle >= PI/4 && text_angle < 3*PI/4) {
            // Texto abajo
            cairo_move_to(cr, text_x - extents.width/2, text_y + extents.height);
        } else if ((text_angle >= 3*PI/4 && text_angle <= PI) || (text_angle >= -PI && text_angle < -3*PI/4)) {
            // Texto a la izquierda
            cairo_move_to(cr, text_x - extents.width, text_y + extents.height/2);
        } else {
            // Texto arriba
            cairo_move_to(cr, text_x - extents.width/2, text_y);
        }

        cairo_show_text(cr, fields[i].name);

        // Mostrar el valor numérico del nivel en el medio del segmento
        if (fields[i].level > 0) {  // Solo mostrar si hay un nivel definido
            double level_text_radius = level_radius * 0.7;
            double level_text_x = center_x + level_text_radius * cos(text_angle);
            double level_text_y = center_y + level_text_radius * sin(text_angle);

            char level_text[10];
            sprintf(level_text, "%d", fields[i].level);

            cairo_text_extents(cr, level_text, &extents);

            // Determinar el color del texto basado en el brillo del fondo
            double brightness = 0.299 * fields[i].color[0] + 0.587 * fields[i].color[1] + 0.114 * fields[i].color[2];
            if (brightness > 0.5) {
                cairo_set_source_rgb(cr, 0, 0, 0);  // Texto negro para fondos claros
            } else {
                cairo_set_source_rgb(cr, 1, 1, 1);  // Texto blanco para fondos oscuros
            }

            cairo_move_to(cr, level_text_x - extents.width / 2, level_text_y + extents.height / 2);
            cairo_show_text(cr, level_text);
        }
    }


    // Guardar la imagen en un archivo PNG
    cairo_status_t status = cairo_surface_write_to_png(surface, filename);

    if (status != CAIRO_STATUS_SUCCESS)
    {
        printf("Error al guardar la imagen: %s\n", cairo_status_to_string(status));
    }

    // Liberar recursos
    cairo_destroy(cr);
    cairo_surface_destroy(surface);
}


