package com.gamingroom.gameauth;

import io.dropwizard.Configuration;
import io.dropwizard.client.JerseyClientConfiguration;

public class GameAuthConfiguration extends Configuration {
	private JerseyClientConfiguration jerseyClient = new JerseyClientConfiguration();
	
	public JerseyClientConfiguration getJerseyClientConfiguration() {
		return jerseyClient;
	}
	
	public void setJerseyClientConfiguration(JerseyClientConfiguration jerseyClient) {
		this.jerseyClient = jerseyClient;
	}
}