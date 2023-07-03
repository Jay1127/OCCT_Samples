using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Forms.Integration;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace DrawShapes
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        DrawShapes_Viewport viewport;

        public MainWindow()
        {
            InitializeComponent();

            ViewPanel.Loaded += ViewPanel_Loaded;

            LayoutUpdated += MainWindow_LayoutUpdated;
            SizeChanged += MainWindow_SizeChanged;
        }

        private void MainWindow_SizeChanged(object sender, SizeChangedEventArgs e)
        {
            if (viewport != null)
            {
                viewport.UpdateResized();
            }
        }

        private void ViewPanel_Loaded(object sender, RoutedEventArgs e)
        {
            // set dimension
            var uc = new System.Windows.Forms.UserControl();
            uc.Width = (int)ViewPanel.ActualWidth;
            uc.Height = (int)ViewPanel.ActualHeight;

            // set handle to viewport
            viewport = new DrawShapes_Viewport();
            viewport.Initialize(uc.Handle);

            // set viewport to viewpanel content
            var host = new WindowsFormsHost();
            host.Child = uc;
            ViewPanel.Content = host;

            viewport.Redraw();
        }

        private void MainWindow_LayoutUpdated(object sender, EventArgs e)
        {
            if (viewport != null)
            {
                viewport.Redraw();
            }
        }

        private void DrawShape(object sender, RoutedEventArgs e)
        {
            var renderItem = (sender as Button).Content.ToString();

            viewport.ClearAll();

            if(renderItem == "Line")
            {
                viewport.DrawLine();
            }
            else if(renderItem == "Segment")
            {
                viewport.DrawSegment();
            }
            else if (renderItem == "Circle")
            {
                viewport.DrawCircle();
            }
            else if (renderItem == "Axis")
            {
                viewport.DrawAxis();
            }
            else if (renderItem == "Point")
            {
                viewport.DrawPoint();
            }
            else if (renderItem == "Text")
            {
                viewport.DrawText();
            }
            else if (renderItem == "Plane")
            {
                viewport.DrawPlane();
            }
            else if (renderItem == "Box")
            {
                viewport.DrawBox();
            }
            else if (renderItem == "Cylinder")
            {
                viewport.DrawCyliner();
            }
        }
    }
}
