# stretch_seeing_eye_planning

## Object Filter Parameters
See `examples/planning_config.yaml` for an example implementation.

`retain_within_bounding_box`: The 2D bounding box (in pixels) used to determine if a detection
should be retained. Expects an array of integers in the following format:
*[x_pos, y_pos, width, height]*, where *x_pos* and *y_pos* point to the top left corner.

`minimum_score`: The minimum confidence score required for a detection to be retained. Expects a
float.
