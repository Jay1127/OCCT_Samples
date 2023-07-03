using System;
using System.Windows;
using System.Windows.Forms.Integration;

namespace HelloOCCT.WPF
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        HelloOCCT_Viewport viewport;

        public MainWindow()
        {
            InitializeComponent();

            ViewPanel.Loaded += ViewPanel_Loaded;
            LayoutUpdated += MainWindow_LayoutUpdated;
        }

        private void ViewPanel_Loaded(object sender, RoutedEventArgs e)
        {
            // set dimension
            var uc = new System.Windows.Forms.UserControl();
            uc.Width = (int)ViewPanel.ActualWidth;
            uc.Height = (int)ViewPanel.ActualHeight;

            // set handle to viewport
            viewport = new HelloOCCT_Viewport();
            viewport.Initialize(uc.Handle);
            viewport.SetBackgroudColor(System.Drawing.Color.Red);

            // set viewport to viewpanel content
            var host = new WindowsFormsHost();
            host.Child = uc;
            ViewPanel.Content = host;
        }

        private void MainWindow_LayoutUpdated(object sender, EventArgs e)
        {
            if (viewport != null)
            {
                viewport.Update();
            }
        }
    }
}
