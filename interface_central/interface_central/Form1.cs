using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO.Ports;
using System.IO;
using System.Net.NetworkInformation;

namespace interface_central
{
    public partial class Form1 : Form
    {

        int timer_semaphore = 0;
        int timer_blink = 0;
        string ledCombination;
        bool active_semaphore = false;
        bool active_blink = false;     
        
        public Form1()
        {
            InitializeComponent();

            serialPort1.PortName = "COM5";
            serialPort1.BaudRate = 9600;
            serialPort1.Open();
            label1.Text = "";
            label2.Text = "";
            label7.Text = "Apagado";
        }


        private void button1_Click(object sender, EventArgs e)
        {
            timer2.Stop();
            timer1.Start();
            active_blink = false;
            blinkasync.CancelAsync();
            timer_semaphore = 0;
            active_semaphore = true;
            label7.Text = "Semáforo";
            if (!backgroundWorker1.IsBusy)
            {
                backgroundWorker1.RunWorkerAsync();
            }
            
            
        }
        private void button2_Click(object sender, EventArgs e)
        {
            timer_semaphore = 0;
            timer1.Stop();
            backgroundWorker1.CancelAsync();
            serialPort1.WriteLine("000000#");
            active_semaphore = false;
            active_blink = true;
            timer2.Start();
            label7.Text = "Pisca Alerta";
            if (!blinkasync.IsBusy)
            {
                blinkasync.RunWorkerAsync();
            }



        }
        private void timer1_Tick(object sender, EventArgs e)
        {
            label1.Text = timer_semaphore.ToString() + " segundos";
            timer_semaphore++;
            
        }
        private void backgroundWorker1_DoWork(object sender, DoWorkEventArgs e) // background worker do semáforo
        {
            while (active_semaphore)
            {
                if (timer_semaphore <= 5)
                {
                    ledCombination = "100001#";
                    pictureBox2.Image = interface_central.Properties.Resources.semaforo_verde;
                    pictureBox3.Image = interface_central.Properties.Resources.semaforo_vermelho;
                }

                else if (timer_semaphore > 5 && timer_semaphore <= 7)
                {
                    ledCombination = "010001#";
                    pictureBox2.Image = interface_central.Properties.Resources.semaforo_amarelo;
                    pictureBox3.Image = interface_central.Properties.Resources.semaforo_vermelho;
                }

                else if (timer_semaphore > 7 && timer_semaphore <= 15)
                {
                    ledCombination = "001100#";
                    pictureBox2.Image = interface_central.Properties.Resources.semaforo_vermelho;
                    pictureBox3.Image = interface_central.Properties.Resources.semaforo_verde;
                }

                else if (timer_semaphore > 15 && timer_semaphore <= 17)
                {
                    ledCombination = "001010#";
                    pictureBox2.Image = interface_central.Properties.Resources.semaforo_vermelho;
                    pictureBox3.Image = interface_central.Properties.Resources.semaforo_amarelo;
                }

                else if (timer_semaphore >= 17)
                {
                    timer_semaphore = 0;
                }

                serialPort1.Write(ledCombination);
                Thread.Sleep(10);
;               backgroundWorker1.ReportProgress(0);

            }
        }

        private void backgroundWorker1_ProgressChanged(object sender, ProgressChangedEventArgs e)
        {
            label2.Text = ledCombination;
            //serialPort1.Write(ledCombination);
        }

        private void blink_async(object sender, DoWorkEventArgs e)
        {
            while (active_blink)
            {
                if (timer_blink <= 1)
                {
                    ledCombination = "010010#";
                    pictureBox2.Image = interface_central.Properties.Resources.semaforo_amarelo;
                    pictureBox3.Image = interface_central.Properties.Resources.semaforo_amarelo;
                } 

                else if (timer_blink > 1 && timer_blink <= 3)
                {
                    ledCombination = "000000#";
                    pictureBox2.Image = interface_central.Properties.Resources.semaforo_apagado;
                    pictureBox3.Image = interface_central.Properties.Resources.semaforo_apagado;
                }

                else if (timer_blink >= 3)
                {
                    timer_blink = 0;
                }

                serialPort1.Write(ledCombination);
                Thread.Sleep(10);
                blinkasync.ReportProgress(0);
            }
        }

        private void blinkasync_ProgressChanged(object sender, ProgressChangedEventArgs e)
        {
            label2.Text = ledCombination;
        }

        private void timer2_Tick(object sender, EventArgs e)
        {
            timer_blink++;
            label1.Text = timer_blink.ToString() + " segundos";
        }

        private void Form1_FormClosed(object sender, FormClosedEventArgs e)
        {
            serialPort1.Write("000000");
            if (serialPort1.IsOpen == true)
            {
                serialPort1.Close();
            }      
        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }

        private void button3_Click(object sender, EventArgs e)
        {
            active_blink = false;
            active_semaphore = false;
            ledCombination = "000000";
            label1.Text = "0";
            label2.Text = ledCombination;
            label7.Text = "Apagado";
            timer1.Stop();
            timer2.Stop();
            serialPort1.Write(ledCombination);
            pictureBox2.Image = interface_central.Properties.Resources.semaforo_apagado;
            pictureBox3.Image = interface_central.Properties.Resources.semaforo_apagado;

        }
    }
}
