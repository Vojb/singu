package com.vojbart.zingu;

import android.app.Activity;
import android.bluetooth.BluetoothDevice;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.util.Log;

import com.macroyau.blue2serial.BluetoothDeviceListDialog;
import com.macroyau.blue2serial.BluetoothSerial;
import com.macroyau.blue2serial.BluetoothSerialListener;

import java.util.ArrayList;
import java.util.List;
import java.util.Set;

/**
 * Created by Vojb on 2018-03-11.
 */

public class BluetoothCom implements BluetoothSerialListener {

    private BluetoothSerial mBluetoothSerial;
    private Context mContext;

    public BluetoothCom(Context context) {

        mContext = context;
        mBluetoothSerial = new BluetoothSerial(mContext, this);
        mBluetoothSerial.setup();
        mBluetoothSerial.start();
    }

    public void showDeviceListDialog() {
        // Display dialog for selecting a remote Bluetooth device
        BluetoothDeviceListDialog dialog = new BluetoothDeviceListDialog(mContext);
        dialog.setOnDeviceSelectedListener(new BluetoothDeviceListDialog.OnDeviceSelectedListener() {
            @Override
            public void onBluetoothDeviceSelected(BluetoothDevice device) {
                connect(device.getAddress());
            }
        });
        dialog.setTitle("find zingu");
        dialog.setDevices(getPairedDevices());
        dialog.showAddress(true);
        dialog.show();
    }

    @Override
    public void onBluetoothNotSupported() {
        Log.v("onBluetoothNotSupported", "onBluetoothNotSupported ");
    }

    @Override
    public void onBluetoothDisabled() {
        Log.v("onBluetoothDisabled", "onBluetoothDisabled ");

    }

    @Override
    public void onBluetoothDeviceDisconnected() {
        Log.v("DISConnecting", "disconnected ");
    }

    @Override
    public void onConnectingBluetoothDevice() {

        Log.v("Connecting", "connecting ");
    }

    @Override
    public void onBluetoothDeviceConnected(String name, String address) {
        Log.v("Connected", name + " : " + address);

    }

    @Override
    public void onBluetoothSerialRead(String message) {
        Log.d("bluetooth recieve", message);
    }

    int currentSpeed;

    @Override
    public void onBluetoothSerialWrite(String message) {

        Log.v("Write", message + " : ");
    }

    public void connect(String address) {
        mBluetoothSerial.connect(address);
    }

    public void write(String message) {
        mBluetoothSerial.write(message);
    }

    public Set<BluetoothDevice> getPairedDevices() {
        return mBluetoothSerial.getPairedDevices();
    }


}
