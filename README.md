# Image Voyager

#***Overview*** :

Image Voyager is a feature-rich image editing software designed to provide users with an intuitive and dynamic interface to manipulate and transform images. Developed using **Qt Framework** for the GUI and **OpenCV** for image processing, the project showcases a seamless integration of advanced technologies for efficient image editing. 

The application supports a variety of image processing features, including blurring, cropping, flipping, grayscale conversion, brightness adjustment, color inversion, gradient application, and more. It also includes essential tools like Undo/Redo functionality and real-time sliders for fine-tuning image parameters.
_____________________________________________________________________________________________________________________________________________________________________________________________________________________________

#***Key Features***
1. **Dynamic File Handling**:
   - Open images of various formats like `.png`, `.jpg`, `.bmp`.
   - Save edited images with custom filenames and locations.

2. **Image Editing Tools**:
   - **Blur**: Apply Gaussian blur with adjustable intensity.
   - **Crop**: Trim images to specified dimensions.
   - **Grayscale**: Toggle between grayscale and original image states.
   - **Flip**: Flip images horizontally or vertically.
   - **Brightness Control**: Adjust brightness dynamically using a slider.
   - **Saturation and Hue**: Modify image vibrance and tones.
   - **Gradient Effect**: Add gradients with real-time control.
   - **Color Inversion**: Create negative versions of images.

3. **Editing Workflow**:
   - **Undo/Redo**: Use stack-based management for editing history.
   - **Live Previews**: Instant feedback for all editing operations.

4. **Information Display**:
   - Displays file properties such as name, size, dimensions, color depth, and channels.

_____________________________________________________________________________________________________________________________________________________________________________________________________________________________

### **Technology Stack**
#### **Core Technologies**:
- **C++**: For high-performance programming and core logic implementation.
- **Qt Framework**: For building the graphical user interface and managing event-driven interactions.
- **OpenCV**: For image processing operations like transformations, color adjustments, and filtering.

#### **Development Tools**:
- **Visual Studio 2022**: IDE used for development and debugging.
- **GitHub**: For version control and project management.

#### **Data Structures Used**:
- **Stack**: Implemented for **Undo/Redo** functionality to manage image states efficiently.

_____________________________________________________________________________________________________________________________________________________________________________________________________________________________

### **Setup Instructions**
#### **Pre-requisites**:
1. **Install Qt Framework**: Download and install from [Qt Official Site](https://www.qt.io).
2. **Install OpenCV**:
   - Ensure that OpenCV is built with MinGW or MSVC, depending on your Qt kit.
3. **Visual Studio 2022** (or any compatible IDE):
   - Configure Visual Studio to link with Qt and OpenCV libraries.

#### **Steps to Build**:
1. Clone the repository:
   ```bash
   git clone https://github.com/amastronaut5/ImageVoyager.git
   cd ImageVoyager
   ```
2. Open the `.sln` file in Visual Studio.
3. Set up the required libraries in project properties:
   - Include paths for **Qt** and **OpenCV**.
   - Link required OpenCV binaries (e.g., `opencv_world410.lib`).
4. Build and run the project.

_____________________________________________________________________________________________________________________________________________________________________________________________________________________________

### **How to Use**
1. **Launching the Application**:
   - Open the application and use the **Browse** button to load an image.

2. **Editing Tools**:
   - Adjust sliders or input fields to fine-tune parameters for blurring, brightness, saturation, and more.
   - Use Undo/Redo buttons to manage your editing workflow.

3. **Saving Your Work**:
   - Save your edits by clicking the **Save** button and specifying the desired filename and format.

4. **View Image Information**:
   - Check the dimensions, size, and color properties of the loaded image in the **Information Section**.

_____________________________________________________________________________________________________________________________________________________________________________________________________________________________

### **References**
1. [Qt Documentation](https://doc.qt.io): Comprehensive guide for Qt framework usage.
2. [OpenCV Documentation](https://docs.opencv.org): For image processing operations and examples.
3. [GitHub Guides](https://docs.github.com): Helped with version control and repository management.
4. [Stack Overflow](https://stackoverflow.com): For troubleshooting technical issues.

_____________________________________________________________________________________________________________________________________________________________________________________________________________________________

### **License**
This project is licensed under the MIT License. See the `LICENSE` file for more details.

_____________________________________________________________________________________________________________________________________________________________________________________________________________________________
