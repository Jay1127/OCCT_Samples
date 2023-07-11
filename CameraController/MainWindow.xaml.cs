using System;
using System.Collections.Generic;
using System.Diagnostics;
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

namespace CameraController
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        CameraController_Viewport viewport;

        int mousePosX;
        int mousePosY;
        bool isDragging = false; // block movemove event when window maximzed, minimized

        public MainWindow()
        {
            InitializeComponent();

            ViewPanel.Loaded += ViewPanel_Loaded;
        }

        private void ViewPanel_Loaded(object sender, RoutedEventArgs e)
        {
            // set dimension
            var uc = new System.Windows.Forms.UserControl();
            uc.Width = (int)ViewPanel.ActualWidth;
            uc.Height = (int)ViewPanel.ActualHeight;

            uc.MouseMove += Viewport_MouseMove;
            uc.MouseDown += Viewport_MouseDown;
            uc.MouseWheel += Viewport_MouseWheel;
            uc.MouseUp += Viewport_MouseUp;
            uc.Paint += Viewport_Paint;
            uc.SizeChanged += Viewport_SizeChanged;

            // set handle to viewport
            viewport = new CameraController_Viewport();
            viewport.Initialize(uc.Handle);

            // set viewport to viewpanel content
            var host = new WindowsFormsHost();
            host.Child = uc;
            ViewPanel.Content = host;

            viewport.MakeModel();
            viewport.Redraw();
        }

        private void Viewport_Paint(object sender, System.Windows.Forms.PaintEventArgs e)
        {
            viewport.Redraw();
        }

        private void Viewport_SizeChanged(object sender, EventArgs e)
        {
            viewport.UpdateResized();
        }

        private void Viewport_MouseUp(object sender, System.Windows.Forms.MouseEventArgs e)
        {
            isDragging = false;
        }

        private void Viewport_MouseDown(object sender, System.Windows.Forms.MouseEventArgs e)
        {
            isDragging = true;

            mousePosX = e.X;
            mousePosY = e.Y;

            if(e.Button == System.Windows.Forms.MouseButtons.Right)
            {
                // set rotation start position
                viewport.StartRotation(e.X, e.Y);
            }
        }

        private void Viewport_MouseWheel(object sender, System.Windows.Forms.MouseEventArgs e)
        {
            viewport.Zoom(e.X, e.Y, e.Delta);
        }

        private void Viewport_MouseMove(object sender, System.Windows.Forms.MouseEventArgs e)
        {
            if(isDragging is false)
            {
                return;
            }

            if (e.Button == System.Windows.Forms.MouseButtons.Left)
            {
                var deltaX = e.X - mousePosX;
                var deltaY = mousePosY - e.Y;
                viewport.Pan(deltaX, deltaY);
            }
            else if (e.Button == System.Windows.Forms.MouseButtons.Right)
            {
                viewport.Rotate(e.X, e.Y);
            }

            mousePosX = e.X;
            mousePosY = e.Y;
            //viewport.MoveTo(e.X, e.Y);
        }
        private void ViewDirectionChanged(object sender, RoutedEventArgs e)
        {
            if(viewport == null)
            {
                return;
            }

            var selectedView = (sender as Button).Content.ToString();

            if(selectedView == "Top")
            {
                viewport.SetTopView();
            }
            else if(selectedView == "Bottom")
            {
                viewport.SetBottomView();
            }
            else if (selectedView == "Front")
            {
                viewport.SetFrontView();
            }
            else if (selectedView == "Rear")
            {
                viewport.SetRearView();
            }
            else if (selectedView == "Left")
            {
                viewport.SetLeftView();
            }
            else if (selectedView == "Right")
            {
                viewport.SetRightView();
            }
            viewport.Redraw();
        }

        private void ViewProjectionChanged(object sender, RoutedEventArgs e)
        {
            if(viewport == null)
            {
                return;
            }

            var chekedProjection = (sender as RadioButton).Content.ToString();

            if(chekedProjection == "Orthogonal")
            {
                viewport.SetOrthogonalProjection();
            }
            else if(chekedProjection == "Perspective")
            {
                viewport.SetPerspectiveProjection();
            }
            viewport.Redraw();
        }

        private void ZoomFit(object sender, RoutedEventArgs e)
        {
            viewport.ZoomFit();
        }
    }
}
