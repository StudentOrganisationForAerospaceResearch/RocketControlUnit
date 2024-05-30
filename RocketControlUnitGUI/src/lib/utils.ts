import { modeCurrent } from '@skeletonlabs/skeleton';

export function rgb_str_to_hex(color: string){
    var rgb_vec = (color.split("(")[1].split(")")[0]).split(",");
    var hex_str = "#";
    hex_str += parseInt(rgb_vec[0]).toString(16);
    hex_str += parseInt(rgb_vec[1]).toString(16);
    hex_str += parseInt(rgb_vec[2]).toString(16);
    return hex_str;
}

export function get_class_color(class_name: string){
    // Create an element with the bg-primary-500 class
    const el = document.createElement('div');
    el.className = class_name;

    document.body.appendChild(el);
    // Get the computed background color
    const color = getComputedStyle(el).backgroundColor;
    // Remove the element from the body
    document.body.removeChild(el);

    return color
}
